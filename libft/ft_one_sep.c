/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_sep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 22:01:22 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/18 00:21:17 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cpy(char *str, char sep, char **new_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == sep)
		i++;
	while (str[i])
	{
		while (str[i] != sep && str[i])
			(*new_str)[j++] = str[i++];
		if (str[i] == sep)
			(*new_str)[j++] = sep;
		while (str[i] == sep && str[i])
			i++;
	}
	(*new_str)[j] = '\0';
}

char	*ft_one_sep(char *str, char sep)
{
	int		i;
	int		count;
	char	*new_str;

	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i] == sep)
		i++;
	while (str[i])
	{
		while (str[i] != sep && str[i++])
			count++;
		if (str[i] == sep)
			count++;
		while (str[i] == sep && str[i])
			i++;
	}
	new_str = (char *)malloc(sizeof(char) * count + 1);
	if (new_str)
		ft_cpy(str, sep, &new_str);
	free(str);
	return (new_str);
}
