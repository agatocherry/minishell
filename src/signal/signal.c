/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:25:04 by shdorlin          #+#    #+#             */
/*   Updated: 2022/03/21 23:22:14 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR);
}

void	sigquit(int signum)
{
	
}
