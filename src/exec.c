/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:49:18 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 22:21:58 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	return (0);
}

int	exec(t_shell *shell, char **env, char **argv)
{
	int		ret;
	char	*cmd;

	cmd = NULL;
	ret = exec2(shell, env, argv, &cmd);
	if (cmd == NULL)
	{
		ret = exec_error(argv[0], ret);
		return (ret);
	}
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		if (execve(cmd, argv, env) == -1)
			ret = exec_error(cmd, ret);
		free(cmd);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	free(cmd);
	return (ret);
}

int	builtin(t_shell *shell, char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv, shell));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (ft_cd(argv, shell));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(shell, argv));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(shell, argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (ft_env(shell));
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
		argv[count++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

void	exec_cmd(t_shell *shell, t_command *cmd)
{
	char	**argv;

	if (shell->first == 0)
		return ;
	if (g_sig.heredoc == 0 || (g_sig.heredoc == 1 && g_sig.sigint == 0))
	{
		argv = cmd_to_argv(cmd);
		if (argv[0] && !ft_strcmp(argv[0], "exit") && !has_type(cmd, PIPE))
			ft_exit(shell, argv);
		else if (argv && is_builtin(argv))
			shell->last_ret = builtin(shell, argv);
		else if (argv)
			shell->last_ret = exec(shell, shell->env, argv);
		free_array(argv);
		free(argv);
		if (shell->last_ret == 32256 || shell->last_ret == 32512)
			shell->last_ret = shell->last_ret / 256;
	}
	ft_close(shell->pipe_in);
	ft_close(shell->pipe_out);
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->first = 0;
	return ;
}
