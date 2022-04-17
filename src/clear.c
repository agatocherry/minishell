/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:52:43 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/18 01:02:58 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_command(t_command *cmd)
{
	t_command	*tmp;

	if (!cmd)
		return ;
	while (cmd && cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->str);
		cmd->str = NULL;
		free(cmd->prev);
		cmd->prev = NULL;
		cmd = tmp;
	}
	free(cmd);
	cmd = NULL;
	return ;
}

void	clear_env(t_shell *shell)
{
	free_array(shell->path);
	free_array(shell->env);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
