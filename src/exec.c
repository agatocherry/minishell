/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:49:18 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/25 00:22:52 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_shell *shell, t_command *cmd)
{
	(void)shell;
	printf("%s lancé\n", cmd->str);
	ft_close(shell->pipe_in);
	ft_close(shell->pipe_out);
	shell->pipe_in = -1;
	shell->pipe_out = -1;
}
