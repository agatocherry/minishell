/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:52:43 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 20:34:41 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_redir(t_command **cmd, int type)
{
	t_command	*prev;
	t_command	*next;
	t_command	*tmp;

	tmp = *cmd;
	while (tmp->prev && tmp->prev->type != PIPE)
		tmp = tmp->prev;
	while (tmp->type != type)
		tmp = tmp->next;
	prev = tmp->prev;
	next = tmp->next->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	ft_memdel((void **)&tmp->str);
	tmp = tmp->next;
	ft_memdel((void **)&tmp->prev);
	ft_memdel((void **)&tmp->str);
	ft_memdel((void **)&tmp);
}

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
	free(shell->path);
	free_array(shell->env);
	free(shell->env);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_memdel((void **)&array[i]);
		i++;
	}
	ft_memdel((void **)&(array[i]));
	ft_memdel((void **)array);
}
