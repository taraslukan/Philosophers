/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:57:26 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/07 12:57:35 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*aft;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		aft = ft_lstlast(*lst);
		if (aft)
			aft->next = new;
	}
	else
		*lst = new;
}
