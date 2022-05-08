/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/09 01:46:35 by shdorlin         ###   ########.fr       */
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
	if (str[++i] == '?' || ft_isdigit(str[i]) == 1)
		i += 1;
	else if (str[i - 1] != '~')
	{
		while (str[i] && break_exp(str[i]) == 0)
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
	int		r;

	var = ft_strdup(&str[*i]);
	r = 1;
	clean_var(&var);
	if (var && var[0] != '~')
		s = get_from_env(shell, &var[1]);
	else
		s = ft_strdup(var);
	if (!s)
	{
		free(var);
		return (NULL);
	}
	if (str[*i] == '~')
		r += 4;
	n_str = (char *)malloc(ft_strlen(str) - ft_strlen(var) + ft_strlen(s) + r);
	if (n_str)
		fill_value(n_str, str, s, i);
	free(var);
	return (n_str);
}

char	*remove_quotes(t_shell *shell, char *str, char *og, int *idx)
{
	char	quote;
	char	*new_str;
	char	*tmp;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, (idx[0] + 1));
	tmp = ft_strjoin(new_str, &str[idx[0] + 1]);
	quote = str[idx[0]++];
	while (str[idx[0]])
	{
		idx[1]++;
		while (og[idx[1]] == '$')
			idx[0] += skip_value(shell, &str[idx[0]], og, &idx[1]);
		if (str[idx[0]++] == quote)
		{
			tmp[idx[0] - 2] = '\0';
			free(new_str);
			new_str = ft_strjoin(tmp, &str[idx[0]]);
			ft_memdel((void **)&tmp);
			break ;
		}
	}
	return (new_str);
}

void	expand_quotes(t_shell *shell, t_command *cmd, char *og)
{
	int		idx[2];
	char	*tmp;

	idx[0] = 0;
	idx[1] = 0;
	while (cmd->str[idx[0]])
	{
		while (og[idx[1]] == '$')
			idx[0] += skip_value(shell, &cmd->str[idx[0]], og, &idx[1]);
		if (cmd->str[idx[0]] == '\'' || cmd->str[idx[0]] == '\"')
		{
			tmp = remove_quotes(shell, cmd->str, og, idx);
			free(cmd->str);
			cmd->str = tmp;
			idx[0] -= 3;
		}
		if (idx[0] == -1 || cmd->str[idx[0]])
			idx[0]++;
		if (og[idx[1]])
			idx[1]++;
	}
	free(og);
	og = NULL;
}

void	expand_cmd(t_shell *shell, t_command *c)
{
	int		i;
	int		quote;
	char	*tmp;

	while (c)
	{
		i = -1;
		quote = 2;
		tmp = ft_strdup(c->str);
		while (c && c->str[++i])
		{
			if (c->str[i] == '\"')
				quote++;
			if (c->str[i] == '\'' && !(quote % 2))
				while (c->str[++i] != '\'')
					;
			if ((c->str[i] == '~' && (!(quote % 2) && (!i
							&& break_exp(c->str[i - 1]))))
				|| (c->str[i] == '$' && ((ft_isalnum(c->str[i + 1])
							&& c->str[i + 1] != '0') || c->str[i + 1] == '?')))
				c->str = expand_value(shell, c->str, &i);
		}
		expand_quotes(shell, c, tmp);
		c = c->next;
	}
}
