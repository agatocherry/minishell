/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/09 00:55:58 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print(int line_break, char **argv, t_shell *shell)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] == '\0')
			i++;
		else
			break ;
	}
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (line_break == 0)
		printf("\n");
}

int	ft_echo(char **argv, t_shell *shell)
{
	int	i;
	int	line_break;

	line_break = 0;
	i = 2;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		while (argv[1][i] == 'n')
			i++;
		if (argv[1][i] == '\0')
			line_break = 1;
	}
	print(line_break, argv, shell);
	return (0);
}
