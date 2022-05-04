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

int	ft_export(t_shell *shell, char **argv)
{
	int		i;
	char	**tmp;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strcmp(argv[1], shell->env[i]) == 0)
			return (0);
		i++;
	}
	shell->env = add_in_env(ft_strdup(argv[1]), shell->env);
	return (0);
}
