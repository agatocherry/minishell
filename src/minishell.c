/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/25 00:59:50 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

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

t_command	*next_run(t_command *cmd)
{
	while (cmd && cmd->type != CMD)
		cmd = cmd->next;
	return (cmd);
}

void	prep_cmd(t_shell *shell, t_command *cmd)
{
	t_command	*prev;
	t_command	*next;
	int			pipe;
	static int	i = 0;

	prev = prev_sep(cmd, 0);
	next = next_sep(cmd, 0);
	pipe = 0;
	i++;
	if (prev)
		printf("%d prev: %s\n", i, prev->str);
	if (cmd)
		printf("%d cmd: %s\n", i, cmd->str);
	if (next)
		printf("%d next: %s\n", i, next->str);
	if (is_type(prev, FD_OUT))
		redir_fd(shell, prev->next, FD_OUT);
	else if (is_type(prev, APPEND))
		redir_fd(shell, prev->next, APPEND);
	else if (is_type(prev, FD_IN))
		redir_fd(shell, prev->next, FD_IN);
//	else if (is_type(prev, LIMIT))
//		here_doc(shell, prev->next);
	else if (is_type(prev, PIPE))
		pipe = pipe_shell(shell);
	printf("what\n");
	if (next && pipe != 1)
		prep_cmd(shell, next->next);
	printf("exec: %d pipe: %d\n", shell->exec, pipe);
	if (pipe != 1 && shell->exec)
	{
		printf("cmd exec: %s\n", cmd->str);
		exec_cmd(shell, cmd);
	}
}

int	launch_shell(t_shell *shell)
{
	t_command	*cmd;
	int			stat;

	cmd = next_run(shell->command);
	if (cmd)
	{
		printf("next_run: %s\n", cmd->str);
		shell->parent = 1;
		shell->last = 1;
		prep_cmd(shell, cmd);
		reset_shell(shell);
		waitpid(-1, &stat, 0);
		stat = WEXITSTATUS(stat);
		if (!shell->last)
			shell->last_ret = stat;
		if (!shell->parent)
		{
			clear_command(&shell->command);
			exit(shell->last_ret);
		}
		shell->exec = 1;
	}
	return (0);
}
