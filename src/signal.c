/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agcolas <agcolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 21:25:04 by shdorlin          #+#    #+#             */
/*   Updated: 2022/04/13 14:09:23 by agcolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_init(void)
{
	// g_sig.sigint = 0; error: ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?
	// g_sig.sigquit = 0; error: ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?
	// g_sig.exit_status = 0; error: ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?
	// g_sig.pid = 0; error: ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?
}

void	sigint(int signum)
{
	(void)signum;
	// if (g_sig.pid) ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?
	// {
	// 	ft_putstr_fd("\n", STDERR);
	// 	g_sig.exit_status = 19;
	// }
	// else
	// {
	// 	ft_putstr_fd("\n", STDERR);
	// 	ft_putstr_fd("$>", STDERR);
		// g_sig.exit_status = 1; error: ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?
	// }
	// g_sig.sigint = 1; error: ‘g_sig’ undeclared (first use in this function); did you mean ‘t_sig’?s
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
**		g_sig.exit_status = 20;
**		g_sig.sigquit = 1;
**	}
**	free(sig);
**}
*/
