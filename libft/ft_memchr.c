/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:49:34 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 23:40:56 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	long unsigned int	i;
	char				c_new;
	char				*s_new;

	i = 0;
	if (n == 0)
		return (NULL);
	s_new = (char *)s;
	c_new = (char)c;
	while (s_new[i] != c_new && i < n - 1)
		i++;
	if (s_new[i] == c_new)
		return (&s_new[i]);
	return (NULL);
}
