/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/28 10:08:50 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*get_command(char **lines)
{
	t_command	*prev;
	t_command	*next;
	int			i;

	prev = NULL;
	next = NULL;
	i = 0;
	while (lines[i])
	{
		next = next_cmd(lines[i++], &prev);
		if (next == NULL)
		{
			clear_command(&prev);
			return (NULL);
		}
		if (prev)
			prev->next = next;
		prev = next;
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

int	type_command(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->command;
	while (cmd)
	{
		if (!(ft_strncmp(cmd->str, "|", 1)))
			cmd->type = PIPE;
		else if (!(ft_strncmp(cmd->str, "<", 1)))
			cmd->type = FD_IN;
		else if (!(ft_strncmp(cmd->str, ">", 1)))
			cmd->type = FD_OUT;
		else if (!(ft_strncmp(cmd->str, ">>", 2)))
			cmd->type = APPEND;
		else if (!(ft_strncmp(cmd->str, "<<", 2)))
			cmd->type = LIMIT;
		else if (cmd->prev == NULL || cmd->prev->type >= PIPE)
			cmd->type = CMD;
		else
			cmd->type = OPT;
	}
	return (0);
}

char	*sep_command(char *line)
{
	char	*new_line;

	new_line = (char *)ft_calloc((count_line(line) + 1), sizeof(char));
	if (new_line)
		parse_line(&new_line, line);
	free(line);
	return (new_line);
}

int	parse_cmd(t_shell *shell)
{
	char	*line;

	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	ft_putstr_fd("$> ", STDIN);
	if (ft_gnl(STDIN, &line) == 0)
		return (0);
	if (g_sig.sigint)
		shell->last_ret = g_sig.exit_status;
	
	if (check_line(shell, &line))
		return (0);
	line = ft_one_sep(line, ' ');
	if (line == NULL)
		return (0);
	line = sep_command(line);
	if (line == NULL)
		return (0);
	shell->command = get_command(ft_split(line, ' '));
	free(line);
	while (shell->command)
	{
		printf("%s\n", shell->command->str);
		shell->command = shell->command->next;
	}
	type_command(shell);
	clear_command(&shell->command);
	return (0);
}
