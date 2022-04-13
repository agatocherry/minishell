/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:52:43 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/13 08:32:46 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_command(t_command *cmd)
{
	t_command   *tmp;

	if (!cmd)
		return ;
	while (cmd->prev)
		cmd = cmd->prev;
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

void	clear_env(t_shell *shell)
{
	free_array(shell->path);
	free_array(shell->env);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
