/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 15:26:59 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char **env, char **argv)
{
	(void)env;
	printf("Depuis unset: %s\n", argv[0]);
	return (0);
}
