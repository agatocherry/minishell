/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:50:44 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/02 22:34:05 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_get_index(const char *s, int c)
{
	int		i;
	char	c_new;

	if (!s)
		return (-1);
	c_new = (char)c;
	i = 0;
	while (s[i] != c_new && s[i])
		i++;
	if (s[i] != c_new)
		return (-1);
	return (i);
}

static char	*ft_get_line(char **save)
{
	char	*line;
	char	*new_save;
	int		index;

	new_save = NULL;
	index = ft_get_index(*save, '\n') + 1;
	if (index == 0)
		line = ft_strdup(*save);
	else
	{
		line = ft_substr(*save, 0, index);
		new_save = ft_strdup(&(*save)[index]);
	}
	free(*save);
	*save = new_save;
	return (line);
}

static char	*ft_read(int fd, char **buf)
{
	int			ret;
	char		*tmp;
	static char	*save = NULL;

	ret = 1;
	tmp = NULL;
	while (ret > 0 && (ft_get_index(save, '\n') == -1))
	{
		ret = read(fd, *buf, BUFFER_SIZE);
		(*buf)[ret] = '\0';
		tmp = save;
		save = ft_gnljoin(tmp, *buf);
		free(tmp);
	}
	free(*buf);
	*buf = NULL;
	return (ft_get_line(&save));
}

int	ft_gnl(int fd, char **line)
{
	char	*buf;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buf = (char *)malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (0);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		return (0);
	}
	*line = ft_read(fd, &buf);
	if (*line == NULL)
		return (0);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	return (1);
}
