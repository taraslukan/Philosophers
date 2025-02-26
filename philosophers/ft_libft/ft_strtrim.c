/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:06:43 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/02 14:44:13 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_s(char val, const char *set);

char	*ft_strtrim(const char *source, const char *set)
{
	char	*s;
	int		i;
	size_t	a;
	size_t	b;

	if (!source || !set)
		return (NULL);
	i = 0;
	a = 0;
	b = ft_strlen(source);
	while (source[a] && c_s(source[a], set))
		a++;
	while (b > a && c_s(source[b - 1], set))
		b--;
	s = (char *)malloc((b - a + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (a < b)
		s[i++] = source[a++];
	s[i] = '\0';
	return (s);
}

static int	c_s(char val, const char *set)
{
	while (*set)
	{
		if (*set == val)
			return (1);
		set++;
	}
	return (0);
}
