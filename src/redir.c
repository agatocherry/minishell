/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:15:11 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 23:11:38 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_prompt(t_command *cmd, char *stop, int fd, int count)
{
	char	*line;

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
		if (!line || ft_strcmp(line, stop) == 0)
			break ;
		else
		{
			write(fd, line, ft_strlen(line));
			free(line);
			line = NULL;
			ft_putstr_fd("> ", STDIN);
			count++;
		}
	}
	free(line);
}

void	here_doc(t_shell *shell, t_command *tmp)
{
	int		fd[2];
	char	*stop;

	signal(SIGINT, &heredoc_sigint);
	if (pipe(fd) == -1)
	{
		shell->fd_in = -1;
		shell->exec = 0;
		shell->last_ret = 1;
		return ;
	}
	stop = ft_strjoin(tmp->str, "\n");
	ft_putstr_fd("> ", STDIN);
	here_prompt(tmp, stop, fd[1], 1);
	free(stop);
	ft_close(fd[1]);
	if (!g_sig.heredoc)
		shell->fd_in = fd[0];
	else
	{
		ft_close(fd[0]);
		shell->fd_in = -1;
	}
	signal(SIGINT, &sigint);
}

void	input_fd(t_shell *shell, t_command **cmd)
{
	t_command	*tmp;

	ft_close(shell->fd_in);
	tmp = *cmd;
	while (tmp && tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp->type != FD_IN && tmp->type != LIMIT)
		tmp = tmp->next;
	tmp = tmp->next;
	if (tmp->prev->type == FD_IN)
		shell->fd_in = open(tmp->str, O_RDONLY, S_IRWXU);
	else
		here_doc(shell, tmp);
	if (tmp->prev->type == FD_IN && shell->fd_in == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(tmp->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->last_ret = 1;
		shell->exec = 0;
		return ;
	}
	if (shell->fd_in == -1)
		return ;
	dup2(shell->fd_in, STDIN);
	remove_redir(cmd, tmp->prev->type);
}

void	redir_fd(t_shell *shell, t_command **cmd)
{
	t_command	*tmp;

	ft_close(shell->fd_out);
	tmp = *cmd;
	while (tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp->type != FD_OUT && tmp->type != APPEND)
		tmp = tmp->next;
	tmp = tmp->next;
	if (tmp->prev->type == FD_OUT)
		shell->fd_out = open(tmp->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	else if (tmp->prev->type == APPEND)
		shell->fd_out = open(tmp->str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (shell->fd_out == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(tmp->str, STDERR);
		ft_putendl_fd(": No such file or directory", STDERR);
		shell->last_ret = 1;
		shell->exec = 0;
		return ;
	}
	dup2(shell->fd_out, STDOUT);
	remove_redir(cmd, tmp->prev->type);
}
