/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:17:31 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/18 00:26:19 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	quotes(char *line)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (line[i])
	{
		if (line[i] == '\"')
			d_quote++;
		if (line[i] == '\'')
			s_quote++;
		i++;
	}
	if ((s_quote % 2) || (d_quote % 2))
		return (1);
	return (0);
}

int	special_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' || line[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	check_line(t_shell *shell, char **line)
{
	if (quotes(*line))
	{
		ft_putendl_fd("Syntax error: non-closed quotes", STDERR);
		free(*line);
		shell->last_ret = 2;
		shell->command = NULL;
		return (1);
	}
	else if (special_char(*line))
	{
		ft_putendl_fd("Syntax error: unknown special character", STDERR);
		free(*line);
		shell->last_ret = 2;
		shell->command = NULL;
		return (1);
	}
	return (0);
}

t_command	*get_command(char *line)
{
	t_command	*prev;
	t_command	*next;
	int			i;
	char		**lines;

	prev = NULL;
	next = NULL;
	i = 0;
	lines = ft_split(line, ' ');
	while (lines[i])
	{
		next = (t_command *)malloc(sizeof(t_command));
//		if (next == NULL)
//			return (NULL);
		next->str = lines[i++];
		next->prev = prev;
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

int	count_line(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			count++;
			i++;
		}
		if (!line[i] && line[i] != ' ')
			count++;
		while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|')
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	parse_line(char **new_line, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			(*new_line)[j++] = line[i];
			i++;
		}
		if (line[i] != '\0' && line[i] != ' ')
			(*new_line)[j++] = ' ';
		while (line[i] && line[i] != '<' && line[i] != '>' && line[i] != '|')
		{
			(*new_line)[j++] = line[i];
			i++;
		}
	}
}

char	*sep_command(char *line)
{
	int		j;
	char	*new_line;

	j = 0;
	new_line = (char *)malloc(sizeof(char) * count_line(line) + 1);
	if (new_line)
		parse_line(&new_line, line);
	free(line);
	return (new_line);
}

int	parse_cmd(t_shell *shell)
{
	char	*line;

	ft_putstr_fd("$> ", STDIN);
	if (ft_gnl(0, &line) == 0)
		return (0);
	if (check_line(shell, &line))
		return (0);
	line = ft_one_sep(line, ' ');
	if (line == NULL)
		return (0);
	line = sep_command(line);
	if (line == NULL)
		return (0);
	shell->command = get_command(line);
	free(line);
	while (shell->command)
	{
		printf("%s\n", shell->command->str);
		shell->command = shell->command->next;
	}
	type_command(shell);
	return (0);
}

t_env *parse_env(char **env)
{
	return (NULL);
}

int	shell_init(t_shell *shell, char **env)
{
	shell->in = dup(STDIN);
	shell->out = dup(STDOUT);
	shell->exit = 0;
	shell->last_ret = 0;
	shell->fd_in = 0;
	shell->fd_out = 0;
	shell->pipe_in = 0;
	shell->pipe_out = 0;
	shell->env = parse_env(env);
	shell->command = NULL;
	return (0);
}

int	launch_shell()
{
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	(void)argc;
	shell_init(&shell, env);
	while (!shell.exit)
	{
		parse_cmd(&shell);
		launch_shell();
	}
	//free ce qu'il faut
	return (shell.last_ret);
}
