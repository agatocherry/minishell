/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/04/18 00:23:19 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sig	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	(void)argc;
	shell_init(&shell, env);
	while (!shell.exit)
	{
		sig_init();
		parse_cmd(&shell);
		if (shell.command != NULL && check_cmd(&shell, shell.command))
			launch_shell(&shell);
		clear_command(shell.command);
	}
	rl_clear_history();
	clear_env(&shell);
	return (shell.last_ret);
}
