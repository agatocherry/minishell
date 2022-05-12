/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 23:50:44 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/12 17:55:23 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*sub;

	if (!s)
		return (NULL);
	sub = (char *)malloc(sizeof (char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*new_s;

	if (!s)
		return (NULL);
	i = 0;
	new_s = (char *)malloc(sizeof (char) * (ft_strlen(s) + 1));
	if (new_s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

int	ft_strchr(const char *s, int c)
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
	static char	*save = NULL;

	ret = 1;
	tmp = NULL;
	while (ret > 0 && (ft_strchr(save, '\n') == -1))
	{
		ret = read(fd, *buf, BUFFER_SIZE);
		(*buf)[ret] = '\0';
		tmp = save;
		save = ft_strjoin(tmp, *buf);
		free(tmp);
	}
	free(*buf);
	*buf = NULL;
	return (ft_get_line(&save));
}

char	*get_next_line(int fd)
{
	char	*buf;

	if (fd < 0 || BUFFER_SIZE < 1)
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
