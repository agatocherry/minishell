/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 19:45:07 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/25 11:33:07 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else
		s += start;
	len++;
	if (len > ft_strlen(s))
		len = ft_strlen(s) + 1;
	sub = (char *)malloc(sizeof (char) * len);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s, len);
	return (sub);
}
