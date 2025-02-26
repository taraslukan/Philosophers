/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:43:38 by tlukan            #+#    #+#             */
/*   Updated: 2025/01/13 23:33:15 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ret = ft_calloc(len + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
    char	*ret;
    size_t	s_len;
    size_t	sub_len;

    if (!s)
        return (NULL);

    s_len = ft_strlen(s);

    // Se `start` è fuori dalla stringa, ritorna una stringa vuota
    if (start >= s_len)
        return (ft_strdup(""));

    // Calcola la lunghezza effettiva della sottostringa
    sub_len = s_len - start;
    if (sub_len > len)
        sub_len = len;

    // Alloca memoria per la sottostringa
    ret = (char *)malloc(sizeof(char) * (sub_len + 1));
    if (!ret)
        return (NULL);

    // Copia i caratteri della sottostringa
    ft_strlcpy(ret, s + start, sub_len + 1);

    return (ret);
}
