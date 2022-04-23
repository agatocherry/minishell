/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/23 22:08:20 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*next_sep(t_command *cmd, int skip)
{
	if (cmd && skip)
		cmd = cmd->next;
	while (cmd && cmd->type < PIPE)
		cmd = cmd->next;
	return (cmd);
}

t_command	*prev_sep(t_command *cmd, int skip)
{
	if (cmd && skip)
		cmd = cmd->prev;
	while (cmd && cmd->type < PIPE)
		cmd = cmd->prev;
	return (cmd);
}

t_command	*next_run(t_command *cmd, int skip)
{
	if (cmd && skip)
		cmd = cmd->next;
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
	return (cmd);
}

void	prep_cmd(t_shell *shell, t_command *cmd)
{
	t_command	*prev;
	t_command	*next;
	int			pipe;

	prev = prev_sep(cmd, 0);
	next = next_sep(cmd, 0);
	pipe = 0;
	if (is_type(prev, FD_OUT))
		redir_fd(shell, cmd, FD_OUT);
	else if (is_type(prev, APPEND))
		redir_fd(shell, cmd, APPEND);
	else if (is_type(prev, FD_IN))
		redir_fd(shell, cmd, FD_IN);
	else if (is_type(prev, PIPE))
		pipe = pipe_shell(shell);
	if (next && pipe != 1)
		exec_cmd(shell, next->next);
	if ((is_type(prev, PIPE) || !prev) && pipe != 1 && shell->exec)
		exec_cmd(shell, cmd);
}

int	launch_shell(t_shell *shell)
{
	t_command	*cmd;

	cmd = next_run(shell->command, 0);
	while (!shell->exit && cmd)
	{
		shell->parent = 1;
		prep_cmd(shell, cmd);
		reset_shell(shell);
		cmd = next_run(cmd, 1);
	}
	return (0);
}
