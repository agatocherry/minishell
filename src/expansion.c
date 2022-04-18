/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:27:09 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/19 00:10:20 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_value(char *new, char *str, char *value)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (str[i] != '$')
		new[j++] = str[i++];
	while (value[n])
		new[j++] = value[n++];
	i++;
	if (str[i] == '?')
		i++;
	else
		while (str[i] && str[i] != ' ')
			i++;
	printf("what");
	while (str[i])
		new[j++] = str[i++];
	printf("what");
	new[j] = '\0';
	printf("what");
	free(value);
}

char	*expand_value(t_shell *shell, char *str)
{
	int		i;
	char	*new_str;
	char	*s;
	char	*value;

	i = 0;
	new_str = NULL;
	value = ft_strdup((ft_strchr(str, '$') + 1));
	if (!value)
		return (NULL);
	if (value[0] == '?')
		value[1] = '\0';
	while (value[i] != ' ' && value[i])
		i++;
	value[i] = '\0';
	if (value[0] == '?')
		s = ft_itoa(shell->last_ret);
	else
		s = getenv(value);
	if (s)
		new_str = (char *)malloc(ft_strlen(str) - ft_strlen(value) + ft_strlen(s));
	if (new_str)
		fill_value(new_str, str, s);
	free(value);
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

void	expand_cmd(t_shell *shell)
{
	char		*tmp;
	t_command	*cmd;

	cmd = shell->command;
	while (cmd)
	{
		while (ft_strchr(cmd->str, '$'))
		{
			tmp = expand_value(shell, cmd->str);
			free(cmd->str);
			cmd->str = tmp;
		}
		if (ft_strchr(cmd->str, '\'') || ft_strchr(cmd->str, '\"'))
			cmd->str = remove_quotes(cmd->str);
		cmd = cmd->next;
	}
}
