/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:34:01 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/03 11:30:04 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	get_fd(t_pipex *pipex, char *arg, int com, char *path)
{
	char	*tmp;

	tmp = NULL;
	if (arg && path)
	{
		arg = ft_strjoin("/", arg);
		tmp = ft_strjoin(path, arg);
		if (access(tmp, X_OK) == 0)
		{
			if (com == 1)
				pipex->command1 = tmp;
			else if (com == 2)
				pipex->command2 = tmp;
			return (0);
		}
		free(arg);
		free(tmp);
	}
	return (-1);
}

void	test_files(t_pipex *pipex, char **args)
{
	pipex->file1_name = args[1];
	pipex->file1 = open(args[1], O_RDONLY);
	if (pipex->file1 == -1)
	{
		perror(args[1]);
		pipex->ret = 0;
		error(pipex);
	}
	pipex->file2 = open(args[4], O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (pipex->file2 == -1)
	{
		perror(args[4]);
		pipex->ret = 0;
		error(pipex);
	}
}
