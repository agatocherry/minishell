/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/27 00:30:20 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_value(char *new, char *str, char *value, int *var)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (i != *var)
		new[j++] = str[i++];
	while (value[n])
		new[j++] = value[n++];
	*var = j - 1;
	if (str[++i] == '?')
		i += 1;
	else
	{
		while (break_exp(str[i]) == 0)
			i++;
	}
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(value);
	free(str);
	str = NULL;
}

char	*expand_value(t_shell *shell, char *str, int *i)
{
	char	*n_str;
	char	*s;
	int		j;
	char	*var;

	var = ft_strdup(&str[*i]);
	if (!var)
		return (NULL);
	if (var[1] == '?')
		var[2] = '\0';
	j = 1;
	while (var[1] != '?' && break_exp(var[j]) == 0)
		j++;
	var[j] = '\0';
	s = get_from_env(shell, &var[1]);
	if (!s)
	{
		free(var);
		return (NULL);
	}
	n_str = (char *)malloc(ft_strlen(str) - ft_strlen(var) + ft_strlen(s) + 1);
	if (n_str)
		fill_value(n_str, str, s, i);
	free(var);
	return (n_str);
}

char	*remove_quotes(char *str, int *i)
{
	int		n;
	int		j;
	char	quote;
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
	n = 0;
	j = 0;
	while (n != *i)
		new_str[j++] = str[n++];
	quote = str[(*i)++];
	while (str[*i] != quote)
		new_str[j++] = str[(*i)++];
	n = *i - 2;
	while (str[++(*i)])
		new_str[j++] = str[*i];
	new_str[j] = '\0';
	*i = n;
	return (new_str);
}

void	expand_quotes(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->str[i])
	{
		if (cmd->str[i] == '\'' || cmd->str[i] == '\"')
		{
			tmp = remove_quotes(cmd->str, &i);
			free(cmd->str);
			cmd->str = tmp;
		}
		i++;
	}
}

void	expand_cmd(t_shell *shell, t_command *cmd)
{
	int			i;
	int			quote;

	while (cmd)
	{
		i = -1;
		quote = 0;
		while (cmd && cmd->str[++i])
		{
			if (cmd->str[i] == '\"')
				quote++;
			if (cmd->str[i] == '\'' && !(quote % 2))
				while (cmd->str[++i] != '\'')
					;
			if (cmd->str[i] == '$' && ((ft_isalnum(cmd->str[i + 1])
						&& cmd->str[i + 1] != '0') || cmd->str[i + 1] == '?'))
				cmd->str = expand_value(shell, cmd->str, &i);
		}
		expand_quotes(cmd);
		cmd = cmd->next;
	}
}
