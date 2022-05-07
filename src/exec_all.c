/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 22:54:40 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 22:00:17 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_error(char *cmd, int ret)
{
	int		fd;
	DIR		*dir;

	fd = open(cmd, O_WRONLY);
	dir = opendir(cmd);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	if (ft_strchr(cmd, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && !dir)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && dir)
		ft_putendl_fd(": Is a directory", STDERR);
	else if (fd != -1 && !dir)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(cmd, '/') == NULL || (fd == -1 && !dir))
		ret = UNK_CMD;
	else
		ret = IS_DIR;
	if (dir)
		closedir(dir);
	ft_close(fd);
	return (ret);
}

char	*join_path_cmd(char	*cmd, char **path, int *ret)
{
	int		i;
	char	*full_cmd;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (ft_strlen(cmd) == 0)
		return (ft_strdup("\0"));
	i = 0;
	full_cmd = NULL;
	while (path[i])
	{
		full_cmd = ft_strjoin(path[i++], cmd);
		if (access(full_cmd, F_OK) == -1)
			*ret = UNK_CMD;
		else if (access(full_cmd, X_OK) == -1)
			*ret = ACC_DENIED;
		else
		{
			*ret = SUCCESS;
			break ;
		}
		free(full_cmd);
		full_cmd = NULL;
	}
	return (full_cmd);
}
