/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:11:08 by agcolas          #+#    #+#             */
/*   Updated: 2022/05/04 18:16:47 by agcolas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_minus(t_shell *shell)
{
	int		i;
	char	**tmp;
	char	*for_chdir;
	int		ret;

	tmp = shell->env;
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "OLDPWD=", 7))
		i++;
	for_chdir = ft_strdup(&tmp[i][7]);
	oldpwd(shell);
	ret = chdir(for_chdir);
	free (for_chdir);
	return (ret);
}

int	if_home(t_shell *shell)
{
	int		i;
	char	**tmp;
	char	*for_chdir;
	int		ret;

	tmp = shell->env;
	i = 0;
	while (tmp[i] && ft_strncmp(tmp[i], "HOME=", 5))
		i++;
	for_chdir = ft_strdup(&tmp[i][5]);
	oldpwd(shell);
	ret = chdir(for_chdir);
	free (for_chdir);
	return (ret);
}

int	exception(char **argv, t_shell *shell)
{
	int	ret;

	ret = -2;
	if (ft_strcmp("-", argv[1]) == 0)
		ret = if_minus(shell);
	if (ft_strcmp("cd", argv[1]) == 0)
		ret = if_home(shell);
	return (ret);
}
