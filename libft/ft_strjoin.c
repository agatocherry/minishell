/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:51:06 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 20:15:36 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = (char *)malloc(sizeof (char) * (i + j + 1));
	if (join == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		join[i] = s1[i];
	while (s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}
