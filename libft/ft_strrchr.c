/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:41:20 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/24 00:10:56 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	c_new;
	char	*s_new;

	s_new = (char *)s;
	c_new = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s_new[i] == c_new)
			return (&s_new[i]);
		i--;
	}
	return (NULL);
}
