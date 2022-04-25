/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:49:18 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/25 02:16:10 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->str, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->str, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->str, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->str, "export") == 0)
		return (1);
	if (ft_strcmp(cmd->str, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd->str, "env") == 0)
		return (1);
	return (0);
}

int	exec(t_shell *shell, char **env, t_command *cmd)
{
	(void)shell;
	(void)env;
	printf("cmd executé: %s\n", cmd->str);
	return (0);
}

int	builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->str, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->str, "cd") == 0)
		return (ft_cd(cmd));
	if (ft_strcmp(cmd->str, "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->str, "export") == 0)
		return (ft_export(shell->env, cmd));
	if (ft_strcmp(cmd->str, "unset") == 0)
		return (ft_unset(shell->env, cmd));
	if (ft_strcmp(cmd->str, "env") == 0)
		return (ft_env(shell->env));
	return (0);
	
}

char	**cmd_to_argv(t_command *cmd)
{
	t_command	*tmp;
	char		**argv;
	int			count;

	tmp = cmd;
	count = 1;
	while (tmp && (tmp->type == CMD || tmp->type == OPT))
	{
		count++;
		tmp = tmp->next;
	}
	argv = (char **)malloc(sizeof(char *) * count);
	if (!argv)
		return (NULL);
	tmp = cmd;
	count = 0;
	while (tmp && (tmp->type == CMD || tmp->type == OPT))
	{
		argv[count++] = tmp->str;
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

void	exec_cmd(t_shell *shell, t_command *cmd)
{
	char	**argv;

	argv = cmd_to_argv(cmd);
	if (shell->first == 0)
		return ;
	if (argv[0] && !ft_strncmp(argv[0], "exit") && !has_pipe(cmd))
		ft_exit(shell, argv);
	else if (argv && is_builtin(argv[0]))
		shell->last_ret = builtin(shell, argv);
	else if (argv)
		shell->last_ret = exec(shell, shell->env, argv);
	free_array(argv);
	ft_close(shell->pipe_in);
	ft_close(shell->pipe_out);
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->first = 0;
	return ;
}
