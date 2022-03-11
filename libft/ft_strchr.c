/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 02:23:55 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/24 00:00:40 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c_new;
	char	*s_new;

	s_new = (char *)s;
	c_new = (char)c;
	i = 0;
	while (s[i] != c_new && s[i])
		i++;
	if (s[i] != c_new)
		return (NULL);
	return (&s_new[i]);
}
