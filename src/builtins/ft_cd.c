/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by agcolas          #+#    #+#             */
/*   Updated: 2022/05/04 18:20:47 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_cd(char **argv, int error)
{
	ft_putstr_fd("minishell: cd: ", STDERR);
	if (argv[1])
	{
		ft_putstr_fd(argv[1], STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (error == 1)
	{
		ft_putendl_fd("Use absolute or relative path", STDERR);
		return ;
	}
	else
		ft_putendl_fd(strerror(errno), STDERR);
}

void	already_have_pwd(t_shell *shell, char *oldpwd)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup("unset");
	tmp[1] = ft_strdup("OLDPWD");
	tmp[2] = NULL;
	ft_unset(shell, tmp);
	shell->env = add_in_env(ft_strjoin("OLDPWD=", oldpwd), shell->env);
	free_array(tmp);
}

void	oldpwd(t_shell *shell)
{
	int		i;
	char	buf[PATH_LEN];
	char	*oldpwd;

	i = 0;
	oldpwd = getcwd(buf, PATH_LEN);
	if (!oldpwd)
		return ;
	while (shell->env[i] && ft_strncmp(shell->env[i], "OLDPWD=", 7))
		i++;
	if (!shell->env[i])
		shell->env = add_in_env(ft_strjoin("OLDPWD=", oldpwd), shell->env);
	else
		already_have_pwd(shell, oldpwd);
}

void	pwd(char **env)
{
	int		i;
	char	buf[PATH_LEN];
	char	*pwd;

	i = 0;
	pwd = getcwd(buf, PATH_LEN);
	if (!pwd)
		return ;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (!env[i])
	{
		env = add_in_env(ft_strjoin("PWD=", pwd), env);
		return ;
	}
	free(env[i]);
	env[i] = ft_strjoin("PWD=", pwd);
}

int	ft_cd(char **argv, t_shell *shell)
{
	int		ret;
	char	*tmp;

	if (!argv[1])
	{
		error_cd(argv, 1);
		ret = ERROR;
	}
	else
	{
		ret = exception(argv, shell);
		if (ret == -2)
		{
			oldpwd(shell);
			ret = chdir(argv[1]);
		}
		ret = check_errors_cd(ret, argv, shell);
	}
	return (ret);
}
