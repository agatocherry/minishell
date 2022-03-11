/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:34:01 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/03 11:15:55 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_pipex	*init_all(void)
{
	t_pipex	*pipex;

	pipex = (t_pipex *)malloc((sizeof(t_pipex)));
	if (!pipex)
		error(pipex);
	pipex->file1 = 0;
	pipex->file2 = 0;
	pipex->file1_name = NULL;
	pipex->command1 = NULL;
	pipex->command2 = NULL;
	pipex->args1 = NULL;
	pipex->args2 = NULL;
	pipex->envp = NULL;
	pipex->paths = NULL;
	pipex->ret = 1;
	return (pipex);
}

pid_t	init_pid(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork ");
		error(pipex);
	}
	return (pid);
}

void	ft_pipex(t_pipex *pipex)
{
	int		end[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(end) == -1)
	{
		perror("Pipe ");
		error(pipex);
	}
	pipex->end = end;
	pid1 = init_pid(pipex);
	if (pid1 == 0)
		first_command(pipex);
	pid2 = init_pid(pipex);
	if (pid2 == 0)
		second_command(pipex);
	close(pipex->end[0]);
	close(pipex->end[1]);
	close(pipex->file1);
	close(pipex->file2);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	pipex->ret = WEXITSTATUS(status);
}

int	main(int num_args, char **args, char **envp)
{
	t_pipex	*pipex;
	char	**paths;

	pipex = NULL;
	if (num_args == 5)
	{
		if (args[2][0] == '\0' || args[3][0] == '\0')
		{
			ft_putstr_fd("One command is empty\n", 2);
			return (1);
		}
		pipex = init_all();
		paths = get_paths(pipex, envp);
		pipex->envp = envp;
		parser(pipex, num_args, args, paths);
		ft_pipex(pipex);
		free_all(pipex);
	}
	else
	{
		ft_putstr_fd("You can use these following example :", 2);
		ft_putstr_fd(" ./pipex file1 cmd1 cmd2 file2", 2);
		return (1);
	}
	return (0);
}
