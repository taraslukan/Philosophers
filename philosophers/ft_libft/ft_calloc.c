/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:29:11 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/26 16:56:10 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ris;

	if (count && size && (4294967295U / size <= count))
		return (0);
	ris = malloc(count * size);
	if (ris == NULL)
		return (NULL);
	ft_bzero(ris, count * size);
	return (ris);
}
