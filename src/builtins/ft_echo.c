/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 20:00:11 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_var(t_shell *shell, char *str)
{
	int		i;
	char	**tmp;

	tmp = shell->env;
	i = 0;
	*str++;
	while (tmp[i] && ft_strncmp(tmp[i], str, ft_strlen(str)))
		i++;
	printf("%s", &tmp[i][ft_strlen(str) + 1]);
}

static void	print(int line_break, char **argv, int len, t_shell *shell)
{
	int	i;
	int	space;

	space = 0;
	i = 1;
	if (line_break == 0)
		i = 2;
	while (argv[i])
	{
		if (argv[i][0] == '$')
			print_var(shell, argv[i]);
		else
			printf("%s", argv[i]);
		i++;
		if (space >= 0 && space + 1 < len)
			printf(" ");
		space++;
	}
	if (line_break == 1)
		printf("\n");
}

int	ft_echo(char **argv, t_shell *shell)
{
	int	len;
	int	line_break;

	len = 0;
	line_break = 1;
	while (argv[len] && argv[len][0] != '|')
		len++;
	if (len >= 2 && argv[1][0] == '-')
	{
		len--;
		line_break = 0;
	}
	len--;
	print(line_break, argv, len, shell);
	return (0);
}
