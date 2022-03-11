/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:38:03 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/24 01:37:18 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	long unsigned int	i;
	char				*dest_new;
	char				*src_new;

	if (src == dest)
		return (dest);
	i = -1;
	dest_new = (char *)dest;
	src_new = (char *)src;
	while (++i < n)
		dest_new[i] = src_new[i];
	return (dest);
}
