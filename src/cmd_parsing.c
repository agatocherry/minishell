/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/05/09 13:52:54 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_command	*get_command(char **lines)
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
	free(lines);
	return (next);
}

static void	type_command(t_shell *shell)
{
	t_command	*cmd;

	cmd = shell->command;
	while (cmd)
	{
		if (!(ft_strcmp(cmd->str, "|")))
			cmd->type = PIPE;
		else if (!(ft_strcmp(cmd->str, "<")))
			cmd->type = FD_IN;
		else if (!(ft_strcmp(cmd->str, ">")))
			cmd->type = FD_OUT;
		else if (!(ft_strcmp(cmd->str, ">>")))
			cmd->type = APPEND;
		else if (!(ft_strcmp(cmd->str, "<<")))
			cmd->type = LIMIT;
		else if (cmd->prev && cmd->prev->type >= FD_IN)
			cmd->type = FIL;
		else if (cmd->prev == NULL || cmd->prev->type == 3 || !cmd->prev->type)
			cmd->type = CMD;
		else
			cmd->type = OPT;
		cmd = cmd->next;
	}
}

static char	*sep_command(char *line)
{
	char	*new_line;

	line = remove_space(line);
	new_line = (char *)ft_calloc((count_line(line) + 1), sizeof(char));
	if (new_line)
		parse_line(new_line, line);
	free(line);
	return (new_line);
}

int	parse_cmd(t_shell *shell)
{
	char	*line;

	signal(SIGINT, &sigint);
	signal(SIGQUIT, &sigquit);
	line = readline("👉 ");
	if (!line)
	{
		shell->exit = 1;
		ft_putendl_fd("exit", STDIN);
		return (0);
	}
	add_history(line);
	if (g_sig.sigint)
		shell->last_ret = g_sig.exit_status;
	if (check_line(shell, &line))
		return (0);
	line = sep_command(line);
	if (line == NULL)
		return (0);
	shell->command = get_command(ft_split_cmd(line));
	free(line);
	type_command(shell);
	expand_cmd(shell, shell->command);
	return (0);
}
