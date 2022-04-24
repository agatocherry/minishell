/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 22:58:50 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/24 21:29:01 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/file.h>
# include <sys/stat.h>
# include <sys/errno.h>

# define STDIN 1
# define STDOUT 2
# define STDERR 3

# define FIL 0
# define CMD 1
# define OPT 2
# define PIPE 3
# define FD_IN 4
# define FD_OUT 5
# define APPEND 6
# define LIMIT 7

# define ERROR 1
# define SUCCESS 0
# define NOT_EXEC 126
# define UNK_CMD 127

typedef struct s_command
{
	char				*str;
	int					type;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_command	*command;
	char		**env;
	char		**cmd_env;
	char		**path;
	int			in;
	int			out;
	int			last_ret;
	int			fd_in;
	int			fd_out;
	int			pipe_in;
	int			pipe_out;
	int			pid;
	int			last;
	int			first;
	int			exec;
	int			parent;
	int			exit;
}	t_shell;

typedef struct s_sig
{
	int		sigint;
	int		sigquit;
	int		exit_status;
	pid_t	pid;
}	t_sig;

/*
** --- src ---
*/

int			shell_init(t_shell *shell, char **env);
int			launch_shell(t_shell *shell);
void		prep_cmd(t_shell *shell, t_command *cmd);

/*
** --- clear ---
*/

void		free_array(char **array);
void		clear_command(t_command **cmd);
void		clear_env(t_shell *shell);

/*
** --- cmd ---
*/

t_command	*get_command(char **lines);
void		type_command(t_shell *shell);
char		*sep_command(char *line);
int			parse_cmd(t_shell *shell);
void		expand_cmd(t_shell *shell, t_command *cmd);

t_command	*next_cmd(char *line, t_command **prev);
int			check_cmd(t_shell *shell, t_command *cm);

int			quotes(char *line);
int			special_char(char *line);
int			check_line(t_shell *shell, char **line);
void		parse_line(char *new_line, char *line);
int			count_line(char *line);
char		*remove_space(char *line);
void		close_quotes(char *line, int *i, int *count);
void		fill_line(char *line, char *new_line, int *i, int *j);

/*
** --- execution ---
*/

void	redir_fd(t_shell *shell, t_command *cmd, int type);
int		pipe_shell(t_shell *shell);
void	exec_cmd(t_shell *shell, t_command *cmd);

/*
** --- utils ---
*/

int			is_special_char(char c);
char		**ft_split_cmd(char *line);
void		reset_shell(t_shell *shell);
int			is_type(t_command *cmd, int type);
void		ft_close(int fd);

/*
** --- env ---
*/

void		parse_env(t_shell *shell, char **env);
char		*incr_shlvl(char *env);
char		*get_from_env(t_shell *shell, char *var);

/*
** --- signal ---
*/

void		sig_init(void);
void		sigint(int signum);
void		sigquit(int signum);

extern t_sig	g_sig;

#endif
