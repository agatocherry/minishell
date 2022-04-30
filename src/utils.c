/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:43:59 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/30 18:03:24 by shdorlin         ###   ########.fr       */
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
	while (tmp && tmp->prev && tmp->prev->type != PIPE)
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

int	break_exp(int c)
{
	if (c == 0)
		return (1);
	if (c >= 32 && c <= 47)
		return (1);
	if (c == 58 || c == 59 || c == 61 || c == 63 || c == 64 || c == 91)
		return (1);
	if ((c >= 93 && c <= 96) || c == 123 || c == 125 || c == 126)
		return (1);
	return (0);
}

void	skip_value(t_shell *shell, char *og, int *i, int *j)
{
	int		n;
	char	*var;
	char	*s;

	var = ft_strdup(&og[*j]);
	clean_var(var);
	s = get_from_env(shell, &var[1]);
	n = 0;
	while (s[n++])
		(*i)++;
	(*j)++;
	while (break_exp(og[*j]) == 0)
		(*j)++;
	free(var);
	free(s);
	return ;
}
