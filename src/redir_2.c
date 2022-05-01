/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:33:04 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/01 23:40:00 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	only_hereprompt(t_command *cmd, char *line)
{
	int	over;

	over = 1;
	while (over)
	{
		if (!line && g_sig.sigint == 0)
		{
			ft_putstr_fd("-minishell: warning: here_document", STDERR);
			ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR);
			ft_putstr_fd(cmd->str, STDERR);
			ft_putendl_fd("')", STDERR);
			over = 0;
		}
		else if (ft_strcmp(line, cmd->str) == 0)
			break ;
		else
		{
			free(line);
			line = readline("> ");
		}
	}
	free(line);
}

void	only_heredoc(t_command *cmd)
{
	pid_t	pid;
	char	*line;

	if (STDOUT != 1)
		return ;
	g_sig.heredoc = 1;
	pid = fork();
	if (pid == 0)
	{
		line = readline("> ");
		only_hereprompt(cmd, line);
		exit(SUCCESS);
	}
	else
		wait(0);
}

void	check_redir(t_shell *shell, t_command *cmd)
{
	int	ret;

	if (!cmd)
		return ;
	while (cmd)
	{
		while (cmd && cmd->type != 0)
			cmd = cmd->next;
		if (cmd && (cmd->prev->type == FD_OUT || cmd->prev->type == APPEND))
			open(cmd->str, O_CREAT, S_IRWXU);
		else if (cmd && cmd->prev->type == FD_IN)
		{
			ret = open(cmd->str, O_RDONLY, S_IRWXU);
			if (ret == -1)
				if_shell_fd_out(shell, cmd);
		}
		else if (cmd && cmd->prev->type == LIMIT)
			only_heredoc(cmd);
		if (cmd)
			cmd = cmd->next;
	}
}
