/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 00:35:17 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/22 00:53:55 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	long unsigned int	i;
	char				*s_new;

	s_new = (char *)s;
	i = -1;
	while (++i < n)
		s_new[i] = '\0';
}
