/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/04 10:38:10 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_where_to_unset(t_shell *shell, char **argv)
{
	int	i;
	int	find;
	int	len;

	find = -1;
	i = 0;
	while (shell->env[i])
	{
		len = 0;
		while (shell->env[i][len]
	&& shell->env[i][len] != '=')
			len++;
		if (ft_strncmp(argv[1], shell->env[i], ft_strlen(argv[1])) == 0
			&& ft_strlen(argv[1]) == len)
		{
			find = i;
			break ;
		}
		i++;
	}
	return (find);
}

int	len_double_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
		i++;
	return (i);
}

void	the_end(t_shell *shell, int where_unset)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * where_unset + 1);
	i = 0;
	while (where_unset > 0 && shell->env[i])
	{
		tmp[i] = ft_strdup(shell->env[i]);
		i++;
		where_unset--;
	}
	tmp[i] = NULL;
	free_array(shell->env);
	shell->env = tmp;
}

void	with_rest(t_shell *shell, int len, int where_unset)
{
	int		rest;
	char	**tmp;
	int		i;
	int		j;

	rest = len - 1 - where_unset;
	tmp = malloc(sizeof(char *) * len - 1);
	i = 0;
	while (where_unset > 0 && shell->env[i])
	{
		tmp[i] = ft_strdup(shell->env[i]);
		i++;
		where_unset--;
	}
	j = i + 1;
	while (i < len - 1 && shell->env[j])
	{
		tmp[i] = ft_strdup(shell->env[j]);
		i++;
		j++;
	}
	tmp[i] = NULL;
	free_array(shell->env);
	shell->env = tmp;
}

int	ft_unset(t_shell *shell, char **argv)
{
	int	where_unset;
	int	len;

	if (!argv[1])
	{
		printf("unset: not enough arguments\n");
		return (0);
	}
	where_unset = find_where_to_unset(shell, argv);
	len = len_double_arrays(shell->env);
	if (len - where_unset > 1)
		with_rest(shell, len, where_unset);
	else
		the_end(shell, where_unset);
	return (0);
}
