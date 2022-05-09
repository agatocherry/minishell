/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by agcolas          #+#    #+#             */
/*   Updated: 2022/05/07 20:00:07 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	error_cd(char **argv)
{
	if (argv[1] && argv[2])
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR);
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR);
		if (argv[1])
		{
			ft_putstr_fd(argv[1], STDERR);
			ft_putstr_fd(": ", STDERR);
		}
		ft_putendl_fd(strerror(errno), STDERR);
	}
}

void	already_have_pwd(t_shell *shell, char *oldpwd)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup("unset");
	tmp[1] = ft_strdup("OLDPWD");
	tmp[2] = NULL;
	ft_unset(shell, tmp);
	shell->env = add_in_env(ft_strjoin("OLDPWD=", oldpwd), shell->env);
	free_array(tmp);
	free(tmp);
}

void	oldpwd(t_shell *shell, char *oldpwd)
{
	int		i;

	i = 0;
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
	char	buf[PATH_LEN];
	char	*n_oldpwd;

	ret = 1;
	if (argv[1] && argv[2])
		error_cd(argv);
	else
		ret = exception(argv, shell);
	if (ret == -2)
	{
		n_oldpwd = getcwd(buf, PATH_LEN);
		ret = chdir(argv[1]);
		if (ret == -1)
			ret *= -1;
		if (ret == 1)
			error_cd(argv);
		if (ret == 0)
		{
			pwd(shell->env);
			oldpwd(shell, n_oldpwd);
		}
	}
	return (ret);
}
