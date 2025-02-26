/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:06:43 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/31 12:02:11 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ris;
	size_t	len;

	len = ft_strlen(s1);
	ris = ft_calloc((len + 1), sizeof(char));
	if (ris == NULL)
		return (NULL);
	ft_strlcpy(ris, s1, len + 1);
	return (ris);
}
