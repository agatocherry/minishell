/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:11:08 by agcolas          #+#    #+#             */
/*   Updated: 2022/05/07 22:24:34 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_minus(t_shell *shell)
{
	int		i;
	char	**tmp;
	char	*for_chdir;
	int		ret;
	char	buf[PATH_LEN];

	tmp = shell->env;
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "OLDPWD=", 7))
		i++;
	if (!tmp[i])
	{
		ft_putstr_fd("minishell: cd: $OLDPWD not set\n", STDERR);
		return (1);
	}
	for_chdir = ft_strdup(&tmp[i][7]);
	getcwd(buf, PATH_LEN);
	oldpwd(shell, buf);
	ret = chdir(for_chdir);
	pwd(shell->env);
	free(for_chdir);
	return (ret);
}

int	if_home(t_shell *shell)
{
	int		i;
	char	**tmp;
	char	buf[PATH_LEN];
	char	*for_chdir;
	int		ret;

	tmp = shell->env;
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "HOME=", 5))
		i++;
	if (!tmp[i])
	{
		ft_putstr_fd("minishell: cd: $HOME not set\n", STDERR);
		return (1);
	}
	for_chdir = ft_strdup(&tmp[i][5]);
	getcwd(buf, PATH_LEN);
	oldpwd(shell, buf);
	ret = chdir(for_chdir);
	pwd(shell->env);
	free(for_chdir);
	return (ret);
}

int	exception(char **argv, t_shell *shell)
{
	int	ret;

	ret = -2;
	if (argv[1] && ft_strcmp("", argv[1]) == 0)
		ret = 0;
	if (argv[1] && ft_strcmp("-", argv[1]) == 0)
		ret = if_minus(shell);
	else if (!argv[1])
		ret = if_home(shell);
	return (ret);
}
