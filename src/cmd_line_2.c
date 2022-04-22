/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:33:21 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/22 21:23:50 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_special_char(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	close_quotes(char *line, int *i, int *count)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	(*count)++;
	while (line[*i] != quote)
	{
		(*i)++;
		(*count)++;
	}
	(*i)++;
	(*count)++;
}

void	fill_line(char *line, char *new_line, int *i, int *j)
{
	char	quote;

	quote = line[*i];
	new_line[(*j)++] = line[(*i)++];
	while (line[*i] != quote)
		new_line[(*j)++] = line[(*i)++];
	new_line[(*j)++] = line[(*i)++];
}

char	*ft_cpy(char *line, int count)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * (count + 1));
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			fill_line(line, new_line, &i, &j);
		while (line[i] != ' ' && line[i])
			new_line[j++] = line[i++];
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] != '\0')
			new_line[j++] = ' ';
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*remove_space(char *line)
{
	int		i;
	int		count;
	char	*new_line;

	i = 0;
	count = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			close_quotes(line, &i, &count);
		while (line[i] != ' ' && line[i])
		{
			i++;
			count++;
		}
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] != '\0')
			count++;
	}
	new_line = ft_cpy(line, count);
	free(line);
	return (new_line);
}
