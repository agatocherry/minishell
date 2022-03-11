/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:37:01 by agcolas           #+#    #+#             */
/*   Updated: 2022/02/24 18:11:24 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	close_pipex(int code)
{
	exit(code);
}

void	free_args(t_pipex *pipex)
{
	int	i;

	if (pipex->args1)
	{
		i = 0;
		while (pipex->args1[i])
		{
			free(pipex->args1[i]);
			pipex->args1[i++] = NULL;
		}
		free(pipex->args1);
		pipex->args1 = NULL;
	}
	if (pipex->args2)
	{
		i = 0;
		while (pipex->args2[i])
		{
			free(pipex->args2[i]);
			pipex->args2[i++] = NULL;
		}
		free(pipex->args2);
		pipex->args2 = NULL;
	}
}

void	free_paths(t_pipex *pipex)
{
	int	i;

	if (pipex->paths)
	{
		i = 0;
		while (pipex->paths[i])
		{
			free(pipex->paths[i]);
			pipex->paths[i++] = NULL;
		}
		free(pipex->paths);
		pipex->paths = NULL;
	}
}

void	free_all(t_pipex *pipex)
{
	int	ret;

	ret = pipex->ret;
	if (pipex->file1)
		close(pipex->file1);
	if (pipex->file2)
		close(pipex->file2);
	if (pipex->command1)
		free(pipex->command1);
	if (pipex->command2)
		free(pipex->command2);
	free_args(pipex);
	free_paths(pipex);
	free(pipex);
	close_pipex(ret);
}
