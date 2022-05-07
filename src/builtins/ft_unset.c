/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 23:48:12 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_where_to_unset(t_shell *shell, char *argv)
{
	int	i;
	int	find;
	int	len;

	find = -1;
	i = 0;
	while (shell->env[i])
	{
		len = 0;
		while (shell->env[i][len] && shell->env[i][len] != '=')
			len++;
		if (ft_strncmp(argv, shell->env[i], ft_strlen(argv)) == 0
			&& ft_strlen(argv) == len)
		{
			find = i;
			break ;
		}
		i++;
	}
	return (find);
}

void	the_end(t_shell *shell, int where_unset)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (where_unset + 1));
	if (!tmp)
		return ;
	i = 0;
	while (where_unset > 0 && shell->env[i])
	{
		tmp[i] = ft_strdup(shell->env[i]);
		i++;
		where_unset--;
	}
	tmp[i] = NULL;
	free_array(shell->env);
	free(shell->env);
	shell->env = tmp;
}

void	with_rest(t_shell *shell, int len, int where_unset)
{
	int		rest;
	char	**tmp;
	int		i;
	int		j;

	rest = len - 1 - where_unset;
	tmp = malloc(sizeof(char *) * len);
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
	free(shell->env);
	shell->env = tmp;
}

int	print_error_unset(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		{
			ft_putstr_fd("minishell: unset: `", STDERR);
			ft_putstr_fd(str, STDERR);
			ft_putendl_fd("': not a valid identifier", STDERR);
			shell->last_ret = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_shell *shell, char **argv)
{
	int	where_unset;
	int	i;
	int	len;
	int	ret;

	if (!argv[1])
		return (0);
	i = 0;
	len = 0;
	shell->last_ret = 0;
	while (shell->env[len])
		len++;
	while (argv[++i])
	{
		ret = print_error_unset(shell, argv[i]);
		if (ret == 0)
		{
			where_unset = find_where_to_unset(shell, argv[i]);
			if (len - where_unset > 1)
				with_rest(shell, len, where_unset);
			else
				the_end(shell, where_unset);
		}
	}
	return (shell->last_ret);
}
