/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:15:11 by agcolas           #+#    #+#             */
/*   Updated: 2022/05/01 02:00:23 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	pipe_shell(t_shell *shell)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(fd[1]);
		dup2(fd[0], STDIN);
		shell->pipe_in = fd[0];
		shell->parent = 0;
		shell->exec = 1;
		shell->pid = -1;
		return (2);
	}
	else
	{
		ft_close(fd[0]);
		dup2(fd[1], STDOUT);
		shell->pipe_out = fd[1];
		shell->pid = pid;
		shell->last = 0;
		return (1);
	}
}
