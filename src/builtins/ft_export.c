/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:11:08 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/26 15:26:52 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(char **env, char **argv)
{
	(void)env;
	printf("Depuis export: %s\n", argv[0]);
	return (0);
}
