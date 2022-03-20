/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 21:03:27 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/20 19:21:53 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static int	ft_incount(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*ft_allocate(char const *s, char c)
{
	int		i;
	char	*splited;

	i = ft_incount(s, c);
	splited = (char *)malloc(sizeof (char) * (i + 1));
	if (splited == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		splited[i] = s[i];
		i++;
	}
	splited[i] = '\0';
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof (char *) * (ft_count(s, c) + 1));
	if (split == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			split[j] = ft_allocate(&s[i], c);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	split[j] = NULL;
	return (split);
}
