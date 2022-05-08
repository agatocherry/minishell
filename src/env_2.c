/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 22:01:06 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/08 22:57:40 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_var(char **var)
{
	int	i;

	i = 1;
	if (!(*var))
		return ;
	if ((*var)[1] == '?' || ft_isdigit((*var)[1]) == 1)
	{
		(*var)[2] = '\0';
		return ;
	}
	while ((*var)[i] && break_exp((*var)[i]) == 0)
		i++;
	(*var)[i] = '\0';
	if (ft_strcmp(*var, "~") == 0)
	{
		free(*var);
		*var = ft_strdup("$HOME");
	}
	return ;
}

char	**replace_env(char *to_add, char **env)
{
	char	**tmp;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (env);
	while (to_add[j] != '=')
		j++;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], to_add, j + 1) == 0)
			tmp[i] = to_add;
		else
			tmp[i] = ft_strdup(env[i]);
	}
	tmp[i] = NULL;
	free_array(env);
	free(env);
	return (tmp);
}

int	is_in_env(char *to_add, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (to_add[j] != '=')
		j++;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_add, j + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**add_in_env(char *to_add, char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (is_in_env(to_add, env))
		return (replace_env(to_add, env));
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (env);
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdup(env[i]);
	tmp[i++] = to_add;
	tmp[i] = NULL;
	i = 0;
	free_array(env);
	free(env);
	return (tmp);
}

char	**default_env(void)
{
	char	*pwd;
	char	buf[PATH_LEN];
	char	**env;

	pwd = getcwd(buf, PATH_LEN);
	env = (char **)malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("SHELL=/bin/bash");
	env[1] = ft_strjoin("PATH=:/usr/local/sbin:/usr/local/bin",
			":/usr/sbin:/usr/bin:/sbin:/bin");
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strjoin("PWD=", pwd);
	env[4] = NULL;
	return (env);
}
