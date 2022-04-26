/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 15:26:49 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(t_shell *shell, char **argv)
{
	shell->exit = 1;
	printf("Depuis exit: %s\n", argv[0]);
	return (0);
}
