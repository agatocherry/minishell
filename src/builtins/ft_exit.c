/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 21:03:02 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *shell, char **argv)
{
	if (!argv[2])
	{
		shell->exit = 1;
		if (!argv[1])
			shell->last_ret = 0;
		else
			shell->last_ret = ft_atoi(argv[1]);
	}
	ft_putendl_fd("exit", STDERR);
	if (argv[2])
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	return (0);
}
