/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:03:27 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/23 17:50:39 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

static int	ft_count(char *line, int i, int count)
{
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (i == 0 || line[i - 1] == ' ')
				count++;
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			i++;
		}
		if (line[i] == ' ')
			i++;
		if (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
		{
			if (i == 0 || line[i - 1] == ' ')
				count++;
			while (line[i] && line[i] != ' ' && !is_quotes(line[i]))
				i++;
		}
	}
	return (count);
}

static int	ft_incount(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] != ' ' && !is_quotes(line[i]) && line[i])
		i++;
	while (line[i] == '\'' || line[i] == '\"')
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
			i++;
		i++;
	}
	while (line[i] != ' ' && line[i])
		i++;
	return (i);
}

static char	*ft_allocate(char *line, int *i)
{
	int		n;
	char	quote;
	char	*splited;

	n = ft_incount(&line[*i]);
	splited = (char *)malloc(sizeof (char) * (n + 1));
	if (splited == NULL)
		return (NULL);
	n = 0;
	while (line[*i] && !is_quotes(line[*i]) && line[*i] != ' ')
		splited[n++] = line[(*i)++];
	while (line[*i] == '\'' || line[*i] == '\"')
	{
		quote = line[*i];
		splited[n++] = line[(*i)++];
		while (line[*i] && line[*i] != quote)
			splited[n++] = line[(*i)++];
		splited[n++] = line[(*i)++];
	}
	while (line[*i] && line[*i] != ' ')
		splited[n++] = line[(*i)++];
	splited[n] = '\0';
	return (splited);
}

char	**ft_split_cmd(char *line)
{
	int		i;
	int		j;
	char	**split;

	split = (char **)malloc(sizeof (char *) * (ft_count(line, 0, 0) + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			split[j++] = ft_allocate(line, &i);
		if (line[i] == ' ')
			i++;
		if (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '\"')
		{
			split[j] = ft_allocate(line, &i);
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}
