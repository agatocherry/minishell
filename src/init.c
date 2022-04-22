/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/04/19 19:29:49 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	shell_init(t_shell *shell, char **env)
{
	int	i;

	i = 0;
	*shell = (t_shell){0};
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	parse_env(shell, env);
	shell->command = NULL;
	while (ft_strncmp(shell->env[i], "SHLVL=", 6))
		i++;
	shell->env[i] = incr_shlvl(shell->env[i]);
	return (0);
}

char	*ft_join(char *str, char c)
{
	char	*new;
	int		i;

	new = (char *)malloc(sizeof (char) * (ft_strlen(str) + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	if (str)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(str);
	str = NULL;
	return (new);
}

char	*incr_shlvl(char *env)
{
	int		n_lvl;
	char	*lvl;
	char	*shlvl;

	n_lvl = ft_atoi(&env[6]) + 1;
	lvl = ft_itoa(n_lvl);
	shlvl = ft_strjoin("SHLVL=", lvl);
	free(env);
	free(lvl);
	return (shlvl);
}
