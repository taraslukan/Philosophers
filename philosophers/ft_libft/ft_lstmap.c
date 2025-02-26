/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:43:23 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/07 14:43:26 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n;
	t_list	*t;

	if (!lst || !f || !del)
		return (0);
	n = NULL;
	while (lst)
	{
		t = ft_lstnew((*f)(lst->content));
		if (!t)
		{
			ft_lstclear(&n, del);
			return (NULL);
		}
		ft_lstadd_back(&n, t);
		lst = lst->next;
	}
	return (n);
}
