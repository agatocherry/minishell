/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:22:47 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/22 01:36:47 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char				*memory;
	long unsigned int	i;

	memory = (void *)malloc(size * nmemb);
	if (memory == NULL)
		return (NULL);
	i = -1;
	while (++i < size * nmemb)
		memory[i] = 0;
	return ((void *)memory);
}
