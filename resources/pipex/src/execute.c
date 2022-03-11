/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:34:01 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/03 13:00:22 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	first_command(t_pipex *pipex)
{
	if (pipex->file1 != -1)
		dup2(pipex->file1, STDIN_FILENO);
	else
	{
		ft_putstr_fd(pipex->file1_name, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		close(pipex->end[0]);
		exit(-1);
	}
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->end[0]);
	execve(pipex->command1, pipex->args1, pipex->envp);
	cmd_not_found(pipex->command1);
	pipex->ret = 127;
	error(pipex);
}

void	second_command(t_pipex *pipex)
{
	dup2(pipex->file2, STDOUT_FILENO);
	dup2(pipex->end[0], STDIN_FILENO);
	close(pipex->end[1]);
	execve(pipex->command2, pipex->args2, pipex->envp);
	cmd_not_found(pipex->command2);
	pipex->ret = 127;
	error(pipex);
}
