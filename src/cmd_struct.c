/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/04/13 14:09:41 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_cmd(t_shell *shell, t_command *cm)
{
	while (cm)
	{
		if (cm->type > PIPE && (!cm->next || cm->next->type > PIPE))
		{
			ft_putstr_fd("Syntax error near unexpected token `", STDERR);
			if (cm->next)
				ft_putstr_fd(cm->next->str, STDERR);
			else
				ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			shell->last_ret = 258;
			return (0);
		}
		if (cm->type == 3 && (!cm->prev || !cm->next || cm->next->type == 3))
		{
			ft_putstr_fd("Syntax error near unexpected token `", STDERR);
			ft_putstr_fd(cm->str, STDERR);
			ft_putstr_fd("newline", STDERR);
			ft_putendl_fd("'", STDERR);
			shell->last_ret = 258;
			return (0);
		}
		cm = cm->next;
	}
	return (1);
}

t_command	*next_cmd(char *line, t_command **prev)
{
	t_command	*next;

	next = ft_calloc(1, sizeof(t_command));
	if (next == NULL)
		return (NULL);
	next->str = line;
	next->prev = *prev;
	return (next);
}
