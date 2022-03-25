/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:17:31 by agcolas           #+#    #+#             */
/*   Updated: 2022/03/25 15:33:27 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void  free_path_env(t_shell *shell)
{
  int  i;

  i = 0;
  while (shell->path_env[i])
  {
    free(shell->path_env[i]);
     i++;
  }
  free(shell->path_env);
}
