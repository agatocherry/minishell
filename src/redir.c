/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:15:11 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/25 23:02:21 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_redir(t_command **cmd, int type)
{
	t_command	*tmp;

	tmp = *cmd;
	while (tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp->type != type)
		tmp = tmp->next;
	tmp->prev->next = tmp->next->next;
	tmp->next->next->prev = tmp->prev;
	ft_memdel((void **)&tmp->str);
	ft_memdel((void **)&tmp->prev);
	tmp = tmp->next;
	ft_memdel((void **)&tmp->str);
	ft_memdel((void **)&tmp->prev);
	ft_memdel((void **)&tmp);
}

void	here_doc(t_shell *shell, t_command **cmd, t_command *tmp)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		shell->fd_in = -1;
		shell->exec = 0;
		return ;
	}
	ft_putstr_fd("> ", STDIN);
	while (ft_gnl(STDIN, &line))
	{
		if (ft_strcmp(line, tmp->str) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
		ft_putstr_fd("> ", STDIN);
	}
	ft_close(fd[1]);
	shell->fd_in = fd[0];
	remove_redir(cmd, LIMIT);
}

void	input_fd(t_shell *shell, t_command **cmd)
{
	t_command	*tmp;

	ft_close(shell->fd_in);
	tmp = *cmd;
	while (tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp->type != FD_IN || tmp->type != LIMIT)
		tmp = tmp->next;
	tmp = tmp->next;
	if (tmp->prev->type == FD_IN)
		shell->fd_in = open(tmp->str, O_RDONLY, S_IRWXU);
	else
		here_doc(shell, cmd, tmp);
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
	while (tmp->type != FD_OUT || tmp->type != APPEND)
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
