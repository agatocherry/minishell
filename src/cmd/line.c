/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/20 20:33:27 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quotes(char *line)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			d_quote++;
		if (line[i] == '\'')
			s_quote++;
		i++;
	}
	if ((s_quote % 2) || (d_quote % 2))
		return (1);
	return (0);
}

int	special_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' || line[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	check_line(t_shell *shell, char **line)
{
	if (quotes(*line))
	{
		ft_putendl_fd("Syntax error: non-closed quotes", STDERR);
		free(*line);
		shell->last_ret = 2;
		shell->command = NULL;
		return (1);
	}
	else if (special_char(*line))
	{
		ft_putendl_fd("Syntax error: unknown special character", STDERR);
		free(*line);
		shell->last_ret = 2;
		shell->command = NULL;
		return (1);
	}
	return (0);
}

void	parse_line(char **new_line, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			(*new_line)[j++] = line[i];
			i++;
		}
		if (i != 0 && line[i] != '\0' && line[i] != ' ')
			(*new_line)[j++] = ' ';
		while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|')
		{
			(*new_line)[j++] = line[i];
			i++;
		}
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			(*new_line)[j++] = ' ';
	}
	(*new_line)[j] = '\0';
}

int	count_line(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			count++;
			i++;
		}
		if (line[i] != '\0' && line[i] != ' ')
			count++;
		while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|')
		{
			count++;
			i++;
		}
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			count++;
	}
	return (count);
}
