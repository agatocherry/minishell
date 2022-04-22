/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/22 15:58:07 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_value(char *new, char *str, char *value, int var)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (i != var)
		new[j++] = str[i++];
	while (value[n])
		new[j++] = value[n++];
	if (str[i + 1] == '?')
		i += 2;
	else
		while (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && str[i])
			i++;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(value);
	free(str);
}

char	*expand_value(t_shell *shell, char *str, int i)
{
	char	*new_str;
	char	*s;
	int		j;
	char	*var;

	var = ft_strdup(&str[i]);
	if (!var)
		return (NULL);
	if (var[1] == '?')
		var[2] = '\0';
	j = 1;
	while (var[j] != ' ' && var[j] != '\'' && var[j] != '\"' && var[j])
		j++;
	var[j] = '\0';
	s = get_from_env(shell, &var[1]);
	if (!s)
	{
		free(var);
		return (NULL);
	}
	new_str = (char *)malloc(ft_strlen(str) - ft_strlen(var) + ft_strlen(s));
	if (new_str)
		fill_value(new_str, str, s, i);
	free(var);
	return (new_str);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
	i = 0;
	j = 0;
	while (str[i] != '\'' && str[i] != '\"')
		new_str[j++] = str[i++];
	quote = str[i++];
	while (str[i] != quote)
		new_str[j++] = str[i++];
	while (str[++i])
		new_str[j++] = str[i];
	new_str[j] = '\0';
	return (new_str);
}

void	expand_quotes(t_command *cmd)
{
	char	*tmp;

	if (ft_strchr(cmd->str, '\"') || ft_strchr(cmd->str, '\''))
	{
		tmp = remove_quotes(cmd->str);
		free(cmd->str);
		cmd->str = tmp;
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
		while (cmd->str[++i])
		{
			if (cmd->str[i] == '\"')
				quote++;
			if (cmd->str[i] == '\'' && !(quote % 2))
				while (cmd->str[++i] != '\'')
					;
			if (cmd->str[i] == '$' && ((ft_isalnum(cmd->str[i + 1]) &&
					cmd->str[i + 1] != '0') || cmd->str[i + 1] == '?'))
				cmd->str = expand_value(shell, cmd->str, i);
		}
		expand_quotes(cmd);
		cmd = cmd->next;
	}
}
