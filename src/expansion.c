/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/01 02:24:48 by shdorlin         ###   ########.fr       */
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
	char	*var;

	var = ft_strdup(&str[*i]);
	if (!var)
		return (NULL);
	clean_var(var);
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

char	*remove_quotes(t_shell *shell, char *str, char *og, int *i, int *j)
{
	char	quote;
	char	*new_str;
	char	*tmp;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_strlcpy(new_str, str, (*i + 1));
	tmp = ft_strjoin(new_str, &str[(*i) + 1]);
	quote = str[(*i)++];
	(*j)++;
	while (str[*i])
	{
		while (og[(*j)] == '$')
			skip_value(shell, str, og, i, j);
		if (str[(*i)++] == quote)
		{
			tmp[(*i) - 2] = '\0';
			new_str = ft_strjoin(tmp, &str[*i]);
			free(tmp);
			break ;
		}
		(*j)++;
	}
	return (new_str);
}

void	expand_quotes(t_shell *shell, t_command *cmd, char *og)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!cmd)
		return ;
	while (cmd->str[i])
	{
		while (og[j] == '$')
			skip_value(shell, cmd->str, og, &i, &j);
		if (cmd->str[i] == '\'' || cmd->str[i] == '\"')
		{
			tmp = remove_quotes(shell, cmd->str, og, &i, &j);
			free(cmd->str);
			cmd->str = tmp;
		}
		if (cmd->str[i])
			i++;
		if (og[j])
			j++;
	}
}

void	expand_cmd(t_shell *shell, t_command *cmd)
{
	int		i;
	int		quote;
	char	*tmp;

	while (cmd)
	{
		i = -1;
		quote = 0;
		tmp = ft_strdup(cmd->str);
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
		expand_quotes(shell, cmd, tmp);
		free(tmp);
		cmd = cmd->next;
	}
}
