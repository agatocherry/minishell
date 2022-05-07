/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 22:54:40 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 19:04:46 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_error(char *cmd, int ret)
{
	DIR		*dir;

	dir = opendir(cmd);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(cmd, STDERR);
	if (ret == ACC_DENIED)
		ft_putendl_fd(": Permission denied", STDERR);
	else if (ret == UNK_CMD)
		ft_putendl_fd(": Command not found", STDERR);
	else if (ret == SUCCESS && dir)
		ft_putendl_fd(": Is a directory", STDERR);
	else
		ft_putendl_fd(": No such file or directory", STDERR);
	if (ret == ACC_DENIED || (ret == SUCCESS && dir))
		ret = IS_DIR;
	else
		ret = UNK_CMD;
	if (dir)
		closedir(dir);
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
