/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftstrchr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:51:03 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/10 14:50:46 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*tempo;

	if (!c)
		return ((char *)(s + ft_strlen(s)));
	tempo = (char *)s;
	while (*tempo)
	{
		if (*tempo == (char)c)
			return (tempo);
		tempo++;
	}
	return (0);
}
