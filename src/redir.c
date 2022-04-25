/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:15:11 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/24 20:31:04 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir_fd(t_shell *shell, t_command *cmd, int type)
{
	if (type == FD_OUT || type == APPEND)
		ft_close(shell->fd_out);
	if (type == FD_IN)
		ft_close (shell->fd_in);
	if (type == FD_OUT)
		shell->fd_out = open(cmd->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (type == APPEND)
		shell->fd_out = open(cmd->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (type == FD_IN)
		shell->fd_in = open(cmd->str, O_RDONLY, S_IRWXU);
	if ((type != FD_IN && shell->fd_out == -1)
			|| (type == FD_IN && shell->fd_in == -1))
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->last_ret = 1;
		shell->exec = 0;
		return ;
	}
	if (type == FD_IN)
		dup2(shell->fd_in, STDIN);
	else
		dup2(shell->fd_out, STDOUT);
}
