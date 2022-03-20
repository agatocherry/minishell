/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:22:47 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/20 19:05:38 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
