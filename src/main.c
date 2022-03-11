/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:47:49 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/11 11:17:35 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell shell;

	shell = (t_shell){0};
	shell.env = get_env(env);
	while (42)
	{
		prompt();
		get_next_line();
		get_command();
		send_to_right_function();
		if (shell.exit == 1)
			exit_function();
	}
	return (0);
}
