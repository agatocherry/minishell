/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/27 00:38:05 by shdorlin         ###   ########.fr       */
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

void	oldpwd(char **env)
{
	int		i;
	char	buf[PATH_LEN];
	char	*oldpwd;

	i = 0;
	oldpwd = getcwd(buf, PATH_LEN);
	if (!oldpwd)
		return ;
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7))
		i++;
	if (!env[i])
	{
		add_in_env(ft_strjoin("OLDPWD=", oldpwd), env);
		return ;
	}
	free(env[i]);
	env[i] = ft_strjoin("OLDPWD=", oldpwd);
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
		add_in_env(ft_strjoin("PWD=", pwd), env);
		return ;
	}
	free(env[i]);
	env[i] = ft_strjoin("PWD=", pwd);
}

int	ft_cd(char **argv, char **env)
{
	int	ret;

	if (!argv[1])
	{
		error_cd(argv, 1);
		ret = ERROR;
	}
	else
	{
		oldpwd(env);
		ret = chdir(argv[1]);
		if (ret == -1)
			ret = ERROR;
		if (ret == ERROR)
			error_cd(argv, 2);
		if (ret == 0)
			pwd(env);
	}
	return (ret);
}
