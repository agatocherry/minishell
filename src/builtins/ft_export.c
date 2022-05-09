/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/09 10:58:02 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_error_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDERR);
			ft_putstr_fd(str, STDERR);
			ft_putendl_fd("': not a valid identifier", STDERR);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	declare_x(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		j = 0;
		while (env[i][j] != '=')
			ft_putchar_fd(env[i][j++], STDOUT);
		ft_putstr_fd("=\"", STDOUT);
		j++;
		while (env[i][j])
			ft_putchar_fd(env[i][j++], STDOUT);
		ft_putendl_fd("\"", STDOUT);
		i++;
	}
}

static int	export_error(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (1);
	if (ft_strchr(str, '=') == NULL)
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (break_exp(str[i]) == 1 && ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_shell *shell, char **argv)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!argv[1])
	{
		declare_x(shell->env);
		return (0);
	}
	while (argv[i])
	{
		if (argv[i] && export_error(argv[i]))
			ret = print_error_export(argv[i]);
		else
			shell->env = add_in_env(ft_strdup(argv[i]), shell->env);
		i++;
	}
	return (ret);
}
