/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 22:01:06 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/30 17:01:06 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_var(char *var)
{
	int	i;

	i = 1;
	if (!var)
		return ;
	if (var[1] == '?')
	{
		var[2] = '\0';
		return ;
	}
	while (var[1] != '?' && break_exp(var[i]) == 0)
		i++;
	var[i] = '\0';
	return ;
}

void	add_in_env(char *to_add, char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i++] = to_add;
	tmp[i] = NULL;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = tmp;
}

char	**default_env(void)
{
	char	*pwd;
	char	buf[PATH_LEN];
	char	**env;

	pwd = getcwd(buf, PATH_LEN);
	env = (char **)malloc(sizeof(char *) * 5);
	env[0] = ft_strdup("SHELL=/bin/bash");
	env[1] = ft_strjoin("PATH=:/usr/local/sbin:/usr/local/bin",
			":/usr/sbin:/usr/bin:/sbin:/bin");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strjoin("PWD=", pwd);
	env[4] = NULL;
	return (env);
}
