/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 16:07:06 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print(int line_break, char **argv, int len)
{
	int	i;
	int	space;

	space = 0;
	i = 1;
	if (line_break == 0)
		i = 2;
	while (argv[i])
	{
		printf("%s", argv[i]);
		i++;
		if (space >= 0 && space + 1 < len)
			printf(" ");
		space++;
	}
	if (line_break == 1)
		printf("\n");
}

int	ft_echo(char **argv)
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
	print(line_break, argv, len);
	return (0);
}
