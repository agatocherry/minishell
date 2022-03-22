/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/20 20:33:27 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	shell_init(t_shell *shell, char **env)
{
	*shell = (t_shell){0};
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->env = parse_env(env);
	shell->command = NULL;
	return (0);
}
