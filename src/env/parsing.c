/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/20 20:33:27 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_path(char **env)
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

char	**parse_env(char **env)
{
	char	*tmp;
	char	**paths;

	tmp = get_path(env);
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp, ':');
	return (NULL);
	if (paths)
		return (paths);
	return (NULL);
}
