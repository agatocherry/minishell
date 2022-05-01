/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:51:50 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/01 23:40:39 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	expand_line(t_shell *shell, char *line)
{
	int		i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ((ft_isalnum(line[i + 1]) && line[i + 1] != '0')
				|| line[i + 1] == '?'))
			line = expand_value(shell, line, &i);
		if (line[i])
			i++;
	}
}
