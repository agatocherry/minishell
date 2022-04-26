/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:52:43 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 16:07:38 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_command(t_command **cmd)
{
	if (!cmd)
		return ;
	while (*cmd && (*cmd)->next)
	{
		ft_memdel((void **)&(*cmd)->str);
		*cmd = (*cmd)->next;
		ft_memdel((void **)&(*cmd)->prev);
	}
	if (*cmd)
	{
		ft_memdel((void **)&(*cmd)->str);
		ft_memdel((void **)&(*cmd));
	}
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
		if (array[i])
			ft_memdel((void **)&array[i]);
		i++;
	}
	if (array)
		ft_memdel((void **)array);
}
