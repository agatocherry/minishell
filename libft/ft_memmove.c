/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:41:39 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/24 02:37:40 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	long unsigned int			i;
	unsigned char				*dest_new;
	unsigned char				*src_new;

	if (src == dest || n == 0)
		return (dest);
	dest_new = (unsigned char *)dest;
	src_new = (unsigned char *)src;
	if (dest_new >= src_new)
	{
		i = n;
		while (--i > 0)
			dest_new[i] = src_new[i];
		dest_new[i] = src_new[i];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}			
