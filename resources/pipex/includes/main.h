/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:37:01 by agcolas           #+#    #+#             */
/*   Updated: 2022/02/17 12:43:41 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

typedef struct s_pipex
{
	int			pid1;
	int			pid2;
	int			file1;
	int			file2;
	int			ret;
	const int	*end;
	char		*file1_name;
	char		*command1;
	char		*command2;
	char		**args1;
	char		**args2;
	char		**envp;
	char		**paths;
}				t_pipex;

t_pipex	*init_all(void);
t_pipex	*parser(t_pipex *pipex, int count, char **args, char **paths);
void	first_command(t_pipex *pipex);
void	second_command(t_pipex *pipex);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		get_fd(t_pipex *pipex, char *arg, int com, char *path);
void	test_files(t_pipex *pipex, char **args);
int		size_array(char **array);
char	*get_path_line(char **paths);
char	**get_paths(t_pipex *pipex, char **envp);
void	free_all(t_pipex *pipex);
void	error(t_pipex *pipex);

#endif