/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:15:11 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/02 19:44:58 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	here_prompt(t_shell *shell, t_command *cmd, char *line, int fd)
{
	int	over;

	over = 1;
	while (over)
	{
		line = expand_line(shell, line);
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
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
			line = readline("> ");
		}
	}
	free(line);
}

void	here_doc(t_shell *shell, t_command *tmp)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (STDOUT != 1)
		return ;
	g_sig.heredoc = 1;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		ft_close(fd[0]);
		line = readline("> ");
		here_prompt(shell, tmp, line, fd[1]);
		ft_close(fd[1]);
		exit(SUCCESS);
	}
	else
	{
		ft_close(fd[1]);
		shell->fd_in = fd[0];
		wait(0);
	}
}

void	if_shell_fd_out(t_shell *shell, t_command	*tmp)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(tmp->str, STDERR);
	ft_putendl_fd(": No such file or directory", STDERR);
	shell->last_ret = 1;
	shell->exec = 0;
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
		if_shell_fd_out(shell, tmp);
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
		if_shell_fd_out(shell, tmp);
		return ;
	}
	dup2(shell->fd_out, STDOUT);
	remove_redir(cmd, tmp->prev->type);
}
