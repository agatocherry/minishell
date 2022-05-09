/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/09 14:27:37 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	error_exit(t_shell *shell, char *argv)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(argv, STDERR);
	ft_putendl_fd(": numeric argument required", STDERR);
	shell->last_ret = 2;
	return (0);
}

static int	exit2(t_shell *shell, char **argv)
{
	int	digit;

	digit = 1;
	shell->exit = 1;
	if (argv[1] && argv[1][0] == '\0')
		digit = error_exit(shell, argv[1]);
	return (digit);
}

int	ft_exit(t_shell *shell, char **argv)
{
	int	i;
	int	digit;

	i = 0;
	ft_putendl_fd("exit", STDERR);
	digit = exit2(shell, argv);
	if (argv[1])
	{
		if (argv[1][i] == '-' || argv[1][i] == '+')
			i++;
		while (argv[1][i] && digit)
			if (ft_isdigit(argv[1][i++]) == 0 || ft_isint(argv[1]) == 0)
				digit = error_exit(shell, argv[1]);
		if (digit)
			shell->last_ret = ft_atoi(argv[1]);
		if (digit && argv[2] != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR);
			shell->last_ret = 1;
			shell->exit = 0;
		}
	}
	return (shell->last_ret);
}
