/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 23:48:18 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
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

void	declare_x(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putendl_fd(env[i], STDOUT);
		i++;
	}
}

int	ft_export(t_shell *shell, char **argv)
{
	int	i;
	int	j;
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
		while (ft_strchr(argv[i], '=') == NULL)
			ret = print_error_export(argv[i++]);
		j = 0;
		while (shell->env[j])
		{
			if (ft_strcmp(argv[i], shell->env[j++]) == 0)
				break ;
		}
		shell->env = add_in_env(ft_strdup(argv[i++]), shell->env);
	}
	return (ret);
}
