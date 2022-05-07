/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/07 20:18:32 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print(int line_break, char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	if (line_break == 1)
		i = 2;
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (argv[i])
			printf(" ");
	}
	if (line_break == 0)
		printf("\n");
}

int	ft_echo(char **argv, t_shell *shell)
{
	int	line_break;

	line_break = 0;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		line_break = 1;
	print(line_break, argv, shell);
	return (0);
}
