/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:05:29 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/29 12:57:59 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ris;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	ris = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ris == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ris[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		ris[i + j] = s2[j];
		j++;
	}
	ris[i + j] = '\0';
	return (ris);
}
