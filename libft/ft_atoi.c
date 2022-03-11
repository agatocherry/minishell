/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:14:23 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 23:05:32 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	x;
	int	signe;

	i = 0;
	x = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			signe *= -1;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		x = x * 10 + (nptr[i] - 48);
		i++;
	}
	return (x * signe);
}
