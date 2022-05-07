/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:49:18 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 20:57:07 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	search_ppath(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp("PATH=", shell->env[i], 5) == 0)
			return (0);
		i++;
	}
	if (str && ft_strchr(str, '/'))
		return (0);
	return (1);
}

int	exec2(t_shell *shell, char **env, char **argv, char **cmd)
{
	int	ret;

	ret = SUCCESS;
	if (search_ppath(shell, argv[0]) == 1)
		return (ret);
	*cmd = join_path_cmd(argv[0], shell->path, &ret);
	if (cmd == NULL)
		return (ret);
	return (ret);
}
