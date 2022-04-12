/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:54:18 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/08 11:14:11 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*itoa;

	nb = n;
	i = ft_count_digits(nb);
	itoa = (char *)malloc(sizeof (char) * (i + 1));
	if (itoa == NULL)
		return (NULL);
	itoa[i--] = '\0';
	if (n == 0)
		itoa[0] = '0';
	else if (n < 0)
	{
		itoa[0] = '-';
		nb *= -1;
	}
	while (n > 0)
	{
		itoa[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	return (itoa);
}
