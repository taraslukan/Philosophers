/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:29:04 by tlukan            #+#    #+#             */
/*   Updated: 2024/01/31 17:49:00 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c);
static size_t	f_w(char const *s, char c, size_t ind_w);
static size_t	let(char const *s, char c, size_t ind_w);

char	**ft_split(char const *s, char c)
{
	char	**ris;
	size_t	ind_w;

	if (!s)
		return (NULL);
	if (!*s)
	{
		ris = ft_calloc(1, sizeof(char *));
		return (ris);
	}
	ind_w = 0;
	ris = ft_calloc((count_word(s, c)) + 1, sizeof(char *));
	if (!ris)
		return (NULL);
	ris[count_word(s, c)] = NULL;
	while (ind_w < count_word(s, c))
	{
		ris[ind_w] = ft_calloc(let(s, c, (ind_w)) + 1, sizeof(char));
		if (!ris[ind_w])
			return (NULL);
		ft_strlcpy(ris[ind_w], (s + f_w(s, c, ind_w)), let(s, c, ind_w) + 1);
		ind_w++;
	}
	return (ris);
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (s[i] != c)
		n++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
			{
				if (s[i + 1] == '\0')
					n--;
				i++;
			}
			n++;
		}
		else
			i++;
	}
	return (n);
}

static size_t	let(char const *s, char c, size_t ind_w)
{
	size_t	i;
	size_t	n;
	size_t	j;

	i = 0;
	n = 0;
	j = 0;
	if (s[i] != c && n <= ind_w)
		n++;
	while (s[i] && n <= ind_w)
	{
		if (s[i] == c)
		{
			while (s[i] == c && n <= ind_w)
				i++;
			n++;
		}
		else
			i++;
	}
	while (s[i + j] != c && s[i + j] != '\0')
		j++;
	return (j);
}

static size_t	f_w(char const *s, char c, size_t ind_w)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (s[i] != c && n <= ind_w)
		n++;
	while (s[i] && n <= ind_w)
	{
		if (s[i] == c)
		{
			while (s[i] == c && n <= ind_w)
				i++;
			n++;
		}
		else
			i++;
	}
	return (i);
}
