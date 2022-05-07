/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/02 16:12:51 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_error_export(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putendl_fd("':not a valid identifier", STDERR);
}

static int	error_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		print_error_export(str);
		return (1);
	}
	while (str[i])
	{
		if (break_exp(str[i]) == 1 && str[i] != '=')
		{
			print_error_export(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_shell *shell, char **argv)
{
	int		i;
	char	**tmp;

	i = 0;
	if (error_export(argv[1]) == 1)
		return (1);
	while (shell->env[i])
	{
		if (ft_strcmp(argv[1], shell->env[i]) == 0)
			return (0);
		i++;
	}
	shell->env = add_in_env(ft_strdup(argv[1]), shell->env);
	return (0);
}
