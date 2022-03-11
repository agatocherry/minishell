/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:54:18 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/24 03:23:22 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	count;

	count = 1;
	while (n / 10 != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	if (str[0] == '-')
		j++;
	while (j < i)
	{
		temp = str[j];
		str[j] = str[--i];
		str[i] = temp;
		j++;
	}
	return (str);
}

static char	*ft_allocate(int n)
{
	char	*itoa;

	if (n == -2147483648)
	{
		itoa = (char *)malloc(sizeof (char) * 12);
		if (itoa == NULL)
			return (NULL);
		ft_strlcpy(itoa, "-2147483648", 12);
		return (itoa);
	}
	if (n < 0)
	{
		n *= -1;
		itoa = (char *)malloc(sizeof (char) * (ft_count_digits(n) + 2));
		if (itoa == NULL)
			return (NULL);
		itoa[0] = '-';
	}
	else
		itoa = (char *)malloc(sizeof (char) * (ft_count_digits(n) + 1));
	if (itoa == NULL)
		return (NULL);
	return (itoa);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*itoa;

	i = 0;
	itoa = ft_allocate(n);
	if (itoa == NULL)
		return (NULL);
	if (n == -2147483648)
		return (itoa);
	if (itoa[0] == '-')
		i++;
	if (n < 0)
		n *= -1;
	while (n / 10 != 0)
	{
		itoa[i++] = (n % 10 + '0');
		n = n / 10;
	}
	itoa[i] = n + '0';
	itoa[i + 1] = '\0';
	return (ft_strrev(itoa));
}
