/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:32:38 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/22 00:53:27 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	long unsigned int	i;
	char				*s_new;

	i = -1;
	s_new = (char *)s;
	while (++i < n)
		s_new[i] = c;
	return (s);
}
