/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:20:57 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/08 19:30:30 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *num)
{
	int	i;
	int	len;

	i = 0;
	if (num[0] == '-' || num[0] == '+')
		i++;
	while (num[i] == '0')
		i++;
	len = ft_strlen(&num[i]);
	if (len == 10)
	{
		if (num[0] == '-' && ft_strcmp(&num[i], "2147483648") > 0)
			return (0);
		if (ft_strcmp(&num[i], "2147483647") > 0)
			return (0);
	}
	if (len > 10)
		return (0);
	return (1);
}
