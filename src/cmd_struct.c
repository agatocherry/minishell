/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/05/09 11:08:45 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	invalid_cmd(t_command *cm)
{
	if (cm->type > PIPE && (!cm->next || cm->next->type >= PIPE))
		return (1);
	if (cm->type == 3 && (!cm->prev || !cm->next || cm->prev->type == 3))
		return (2);
	if (!ft_strncmp(cm->str, "<<", 2) || !ft_strncmp(cm->str, ">>", 2))
		if (cm->str[2] != '\0')
			return (2);
	if (cm->str[0] == '|' && cm->str[1] != '\0')
		return (2);
	return (0);
}

int	check_cmd(t_shell *shell, t_command *cm)
{
	while (cm)
	{
		if (invalid_cmd(cm))
		{
			ft_putstr_fd("Syntax error near unexpected token `", STDERR);
			if (invalid_cmd(cm) == 1)
			{
				if (cm->next)
					ft_putstr_fd(cm->next->str, STDERR);
				else
					ft_putstr_fd("newline", STDERR);
			}
			else
				ft_putchar_fd(cm->str[0], STDERR);
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
