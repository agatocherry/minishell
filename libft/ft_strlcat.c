/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:52:11 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 14:19:32 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	long unsigned int	dst_size;
	long unsigned int	src_size;
	long unsigned int	i;

	dst_size = 0;
	src_size = 0;
	i = 0;
	while (src[src_size])
		src_size++;
	while (dst[dst_size] && dst_size < size)
		dst_size++;
	if (dst_size == size)
		return (size + src_size);
	while (src[i] && dst_size + i < size - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + src_size);
}
