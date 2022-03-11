/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:57:43 by shdorlin          #+#    #+#             */
/*   Updated: 2021/11/23 23:04:37 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*next;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	if (!new)
		return (NULL);
	next = new;
	temp = lst->next;
	while (temp)
	{
		next->next = ft_lstnew((*f)(temp->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		next = next->next;
		temp = temp->next;
	}
	return (new);
}
