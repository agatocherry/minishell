/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/04 20:54:56 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_cmd(t_command *cmd)
{
	char	*tmp;

	while (cmd)
	{
		if (ft_strchr(cmd->str, '$'))
		{
			tmp = cmd->str;
			cmd->str = getenv(&(cmd->str)[1]);
			free(tmp);
			tmp = NULL;
		}
		cmd = cmd->next;
	}
}
