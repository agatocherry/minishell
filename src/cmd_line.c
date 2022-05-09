/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/05/09 11:06:53 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	quotes(char *line)
{
	char	quote;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote = line[i++];
			if (!line[i])
				return (1);
			while (line[i] != quote)
			{
				if (line[i + 1] == '\0')
					return (1);
				i++;
			}
		}
	}
	return (0);
}

static int	special_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
				i++;
		}
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		if (line[i] == '\\' || line[i] == ';')
			return (1);
		if (line[i])
			i++;
	}
	return (0);
}

int	check_line(t_shell *shell, char **line)
{
	if (!line)
		return (2);
	if (!ft_strlen(*line))
	{
		free(*line);
		return (2);
	}
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

void	parse_line(char *new_line, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			fill_line(line, new_line, &i, &j);
		while (!is_special_char(line[i]) && line[i])
			new_line[j++] = line[i++];
		if (line[i] && line[i] != '\'' && line[i] != '\"')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_line[j++] = ' ';
			while (line[i] == '<' || line[i] == '>' || line[i] == '|')
				new_line[j++] = line[i++];
			if (line[i] != ' ')
				new_line[j++] = ' ';
		}
	}
	new_line[j] = '\0';
}

int	count_line(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			close_quotes(line, &i, &count);
		while (!is_special_char(line[i]) && line[i] && line[i++])
			count++;
		if (line[i] && line[i] != '\'' && line[i] != '\"')
		{
			if (i != 0 && line[i - 1] != ' ')
				count++;
			while (line[i] == '<' || line[i] == '>' || line[i] == '|')
			{
				i++;
				count++;
			}
			if (line[i] != ' ')
				count++;
		}
	}
	return (count);
}
