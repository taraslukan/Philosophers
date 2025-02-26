/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:52:52 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/05 16:52:59 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ris;
	size_t			len;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ris = ft_calloc((len + 1), (sizeof(char)));
	if (!ris)
		return (NULL);
	while (s[i])
	{
		ris[i] = f(i, (char)s[i]);
		i++;
	}
	return (ris);
}
