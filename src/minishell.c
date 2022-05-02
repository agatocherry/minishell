/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/02 17:09:05 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

t_command	*next_pipe(t_command *cmd)
{
	while (cmd && cmd->type != PIPE)
		cmd = cmd->next;
	return (cmd);
}

t_command	*prev_pipe(t_command *cmd)
{
	while (cmd && cmd->type != PIPE)
		cmd = cmd->prev;
	return (cmd);
}

t_command	*next_run(t_command *cmd)
{
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
	return (cmd);
}

/*
**	Pipe à partir d'ici de la ligne 50
*/

void	prep_cmd(t_shell *shell, t_command *cmd)
{
	t_command	*next;
	int			pipe;

	pipe = 0;
	next = next_pipe(cmd);
	if (next && is_type(next, PIPE) && shell->exec)
		pipe = pipe_shell(shell);
	if (next && is_type(next, PIPE) && pipe == 2 && shell->exec)
		prep_cmd(shell, next->next);
	while ((has_type(cmd, FD_OUT) || has_type(cmd, APPEND)) && shell->exec)
		redir_fd(shell, &cmd);
	while ((has_type(cmd, FD_IN) || has_type(cmd, LIMIT)) && shell->exec)
		input_fd(shell, &cmd);
	if (pipe != 1 && shell->exec)
		exec_cmd(shell, cmd);
}

int	launch_shell(t_shell *shell)
{
	t_command	*cmd;
	int			status;

	cmd = next_run(shell->command);
	if (cmd)
	{
		shell->first = 1;
		shell->parent = 1;
		shell->last = 1;
		prep_cmd(shell, cmd);
		reset_shell(shell);
		waitpid(-1, &shell->status, 0);
		status = WEXITSTATUS(shell->status);
		if (!shell->last)
			shell->last_ret = status;
		if (!shell->parent)
		{
			clear_command(&shell->command);
			exit(shell->last_ret);
		}
		shell->exec = 1;
	}
	else
		check_redir(shell, shell->command);
	return (0);
}
