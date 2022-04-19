/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/04/19 09:15:57 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_from_env(t_shell *shell, char *var)
{
	int	i;

	i = 0;
	if (var[0] == '?')
		return (ft_itoa(shell->last_ret));
	while (shell->env[i])
	{
		if (ft_strncmp(var, shell->env[i], ft_strlen(var)) == 0)
			return (ft_strdup(&(shell->env[i])[ft_strlen(var) + 1]));
		i++;
	}
	return (ft_strdup(""));
}

static	char	*search_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	**get_path(char **env)
{
	char	*tmp;
	char	**paths;

	tmp = search_path(env);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	if (paths)
		return (paths);
	return (NULL);
}

static char	**get_env(char **env)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = NULL;
	if (tmp)
		return (tmp);
	return (NULL);
}

void	parse_env(t_shell *shell, char **env)
{
	shell->path = get_path(env);
	shell->env = get_env(env);
}
