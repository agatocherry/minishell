/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:46:54 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 14:46:30 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	i;
	unsigned char		*s1_new;
	unsigned char		*s2_new;

	i = 0;
	if (n == 0)
		return (0);
	s1_new = (unsigned char *)s1;
	s2_new = (unsigned char *)s2;
	while (s1_new[i] && s2_new[i] && s1_new[i] == s2_new[i] && i < n - 1)
		i++;
	return (s1_new[i] - s2_new[i]);
}
