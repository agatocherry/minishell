/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/19 09:42:04 by shdorlin         ###   ########.fr       */
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
	printf("%s\n", new_str);
	return (new_str);
}

char	*remove_quotes(char *str)
{
	long unsigned int		i;
	char					*new_str;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
	i = 1;
	while (i < ft_strlen(str) - 1)
	{
		new_str[i - 1] = str[i];
		i++;
	}
	new_str[i - 1] = '\0';
	return (new_str);
}

void	expand_cmd(t_shell *shell, t_command *cmd)
{
	int			i;
	char		*tmp;

	i = 0;
	while (cmd)
	{
		while (cmd->str[i])
		{
			if (cmd->str[i] == '\'')
				while (cmd->str[++i] != '\'')
					;
			if (cmd->str[i] == '$' && ((ft_isalnum(cmd->str[i + 1]) &&
					cmd->str[i + 1] != '0') || cmd->str[i + 1] == '?'))
			{
				tmp = expand_value(shell, cmd->str, i);
				free(cmd->str);
				cmd->str = tmp;
			}
			i++;
		}
		if (ft_strchr(cmd->str, '\'') || ft_strchr(cmd->str, '\"'))
			cmd->str = remove_quotes(cmd->str);
		cmd = cmd->next;
	}
}
