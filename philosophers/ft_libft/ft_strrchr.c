/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:02:24 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/29 17:00:43 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	c_c;

	c_c = (char)c;
	i = ft_strlen(s);
	if (c_c == '\0')
		return ((char *)(s + ft_strlen(s)));
	while (i--)
	{
		if (s[i] == c_c)
			return ((char *)(s + i));
	}
	return (NULL);
}
