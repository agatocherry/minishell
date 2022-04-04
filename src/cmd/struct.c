/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/04/04 10:01:46 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_cmd(t_shell *shell, t_command *cmd)
{
	(void)shell;
	(void)cmd;
	return (0);
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

void	clear_command(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		printf("%s\n", cmd->str);
		free(cmd->str);
		free(cmd->prev);
		cmd = tmp;
	}
	free(cmd);
	cmd = NULL;
	return ;
}
