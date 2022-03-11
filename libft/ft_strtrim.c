/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:00:01 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 20:26:08 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		beg;
	int		end;
	int		i;
	char	*trim;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	beg = 0;
	while (s1[beg] && ft_isset(set, s1[beg]))
		beg++;
	end = ft_strlen(s1);
	while (end > beg && ft_isset(set, s1[end - 1]))
		end--;
	trim = (char *)malloc(sizeof (char) * ((end - beg) + 1));
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (beg < end)
		trim[i++] = s1[beg++];
	trim[i] = '\0';
	return (trim);
}
