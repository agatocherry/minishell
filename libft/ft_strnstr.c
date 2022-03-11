/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:03:27 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 19:53:16 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	long unsigned int	i;
	long unsigned int	j;
	char				*s1_new;

	i = 0;
	s1_new = (char *)s1;
	if (s2[i] == '\0')
		return (s1_new);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s1[i + j] == s2[j] && (i + j) < n)
		{
			if (s2[j + 1] == '\0')
				return (&s1_new[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
