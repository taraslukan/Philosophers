/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:19:33 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/29 16:22:22 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*uc_dst;
	char	*uc_src;

	i = 0;
	uc_dst = (char *)dst;
	uc_src = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (uc_src < uc_dst)
	{
		i = n;
		while (i--)
			uc_dst[i] = uc_src[i];
	}
	else
	{
		while (i < n)
		{
			uc_dst[i] = uc_src[i];
			i++;
		}
	}
	return (dst);
}
