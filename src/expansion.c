/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/13 14:09:33 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
