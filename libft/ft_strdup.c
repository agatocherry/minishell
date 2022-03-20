/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 03:31:41 by shdorlin          #+#    #+#             */
/*   Updated: 2022/02/28 12:45:27 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*new_s;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	new_s = (char *)malloc(sizeof (char) * i + 1);
	if (new_s == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}
