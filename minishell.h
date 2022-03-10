/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:58:50 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/11 00:01:20 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# define STDIN 1
# define STDOUT 2
# define STDERR 3

# define EMPTY 0
# define PIPE 1
# define CMD 2
# define OPT 3

# define ERROR 1
# define SUCCESS 0
# define UNK_CMD 127

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char				*str;
	int					type;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_env		*env;
	t_command	*command;
	int			in;
	int			out;
	int			last_ret;
	int			fd;
	int			pipe_in;
	int			pipe_out;
}	t_shell;

typedef struct s_sig
{
	pid_t	pid;
}	t_sig;

#endif
