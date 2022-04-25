/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:43:59 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/25 21:44:13 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_type(t_command *cmd, int type)
{
	if (cmd && cmd->type == type)
		return (1);
	return (0);
}

int	has_type(t_command *cmd, int type)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == type)
			return (1);
		if (tmp->type == PIPE)
			return (0);
		tmp = tmp->next;
	}
	return (0);
}

void	reset_shell(t_shell *shell)
{
	dup2(shell->in, STDIN);
	dup2(shell->out, STDOUT);
	ft_close(shell->fd_in);
	ft_close(shell->fd_out);
	ft_close(shell->pipe_in);
	ft_close(shell->pipe_out);
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->pid = -1;
}
