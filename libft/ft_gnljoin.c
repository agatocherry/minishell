/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnljoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 20:39:02 by shdorlin          #+#    #+#             */
/*   Updated: 2022/02/27 20:39:28 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnljoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = (char *)malloc(sizeof (char) * (i + j + 1));
	if (join == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i] != '\0')
		join[i] = s1[i];
	while (s2[++j] != '\0')
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (join);
}
