/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:50:44 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/29 02:44:54 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char **save)
{
	char	*line;
	char	*new_save;
	int		index;

	new_save = NULL;
	index = ft_strchr(*save, '\n') + 1;
	if (index == 0)
	{
		index = ft_strchr(*save, '\0') + 1;
		line = ft_strdup(*save);
	}
	else
	{
		line = ft_substr(*save, 0, index);
		new_save = ft_strdup(&(*save)[index]);
	}
	free(*save);
	*save = new_save;
	if ((*line) == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*ft_read(int fd, char **buf)
{
	int			ret;
	char		*tmp;
	static char	*save[MAX_FD];

	ret = 1;
	tmp = NULL;
	while (ret > 0 && (ft_strchr(save[fd], '\n') == -1))
	{
		ret = read(fd, *buf, BUFFER_SIZE);
		(*buf)[ret] = '\0';
		tmp = save[fd];
		save[fd] = ft_strjoin(tmp, *buf);
		free(tmp);
	}
	free(*buf);
	*buf = NULL;
	return (ft_get_line(&save[fd]));
}

char	*get_next_line(int fd)
{
	char	*buf;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 256)
		return (NULL);
	buf = (char *)malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		return (NULL);
	}
	return (ft_read(fd, &buf));
}
