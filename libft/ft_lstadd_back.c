/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:20:32 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/24 03:24:41 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*next;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		next = ft_lstlast(*alst);
		next->next = new;
		return ;
	}
	*alst = new;
}
