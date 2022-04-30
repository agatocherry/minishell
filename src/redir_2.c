/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:33:04 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/30 22:22:15 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	only_hereprompt(t_command *cmd, char *stop, int count)
{
	char *line;

	while (ft_gnl(STDIN, &line) && !g_sig.heredoc)
	{
		if (!line)
		{
			ft_putstr_fd("-minishell: warning: here_document at line ", STDERR);
			ft_putnbr_fd(count, STDERR);
			ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR);
			ft_putstr_fd(cmd->str, STDERR);
			ft_putendl_fd("')", STDERR);
		}
		else if (ft_strcmp(line, stop) == 0)
			break ;
		else
		{
			free(line);
			line = NULL;
			ft_putstr_fd("> ", STDOUT);
			count++;
		}
	}
	free(line);
}

void	only_heredoc(t_command *cmd)
{
	char	*stop;

	if (STDOUT != 1)
		return ;
	stop = ft_strjoin(cmd->str, "\n");
	ft_putstr_fd("> ", STDOUT);
	only_hereprompt(cmd, stop, 1);
	free(stop);
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
