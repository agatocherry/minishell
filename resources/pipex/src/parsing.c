/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:34:01 by agcolas           #+#    #+#             */
/*   Updated: 2022/02/24 18:03:29 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*get_fun(char *arg, char **paths)
{
	int		i;
	char	*tmp;
	char	*join;

	if (ft_strchr(arg, '/') != NULL)
		return (ft_strdup(arg));
	else
	{
		i = 0;
		join = ft_strjoin("/", arg);
		while (paths[i])
		{
			tmp = ft_strjoin(paths[i], join);
			if (access(tmp, X_OK) == 0)
			{
				free(join);
				return (tmp);
			}
			free(tmp);
			i++;
		}
		free(join);
	}
	return (ft_strdup(arg));
}

void	get_args(t_pipex *pipex, char **args)
{
	pipex->args1 = ft_split(args[2], ' ');
	pipex->args2 = ft_split(args[3], ' ');
}

t_pipex	*parser(t_pipex *pipex, int count, char **args, char **paths)
{
	if (count == 5)
	{
		test_files(pipex, args);
		get_args(pipex, args);
		pipex->command1 = get_fun(pipex->args1[0], paths);
		pipex->command2 = get_fun(pipex->args2[0], paths);
		if (!pipex->command1 || !pipex->command2)
			error(pipex);
		return (pipex);
	}
	error(pipex);
	return (NULL);
}
