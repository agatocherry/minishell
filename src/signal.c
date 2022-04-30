/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:25:04 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/30 20:34:55 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.exit_status = 0;
	g_sig.heredoc = 0;
	g_sig.pid = 0;
}

void	sigint(int signum)
{
	(void)signum;
	if (g_sig.pid)
	{
		ft_putstr_fd("\n", STDERR);
		g_sig.exit_status = 130;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.exit_status = 1;
	}
	g_sig.sigint = 1;
}

/*void	sigquit(int signum)
**{
**	char	*sig;
**
**	sig = ft_itoa(signum);
**	if (g_sig.pid)
**	{
**		ft_putstr_fd("Quit : ", STDERR);
**		ft_putendl_fd(sig, STDERR);
**		g_sig.exit_status = 131;
**		g_sig.sigquit = 1;
**	}
**	free(sig);
**}
*/
