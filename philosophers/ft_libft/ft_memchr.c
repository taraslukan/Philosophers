/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:53:22 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/02 12:48:28 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	u_c;
	unsigned char	*u_s;

	u_c = (unsigned char)c;
	u_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (u_s[i] == u_c)
			return ((void *)u_s + i);
		else
			i++;
	}
	return (NULL);
}
