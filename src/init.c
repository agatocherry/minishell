/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/04/11 16:44:36 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	shell_init(t_shell *shell, char **env)
{
	*shell = (t_shell){0};
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	parse_env(shell, env);
	shell->command = NULL;
	increment_shlvl(shell->env);
	return (0);
}
