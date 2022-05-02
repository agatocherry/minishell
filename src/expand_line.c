/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:51:50 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/02 12:59:39 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_line(t_shell *shell, char *line)
{
	int		i;
	char	*new_line;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && ((ft_isalnum(line[i + 1]) && line[i + 1] != '0')
				|| line[i + 1] == '?'))
			line = expand_value(shell, line, &i);
		if (line[i])
			i++;
	}
	new_line = ft_strdup(line);
	free(line);
	return (new_line);
}
