/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:27:28 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/02 16:51:51 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	nblen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n && ++len)
		n /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*b;
	char	*ris;
	int		len;

	b = "0123456789";
	len = nblen(n);
	ris = (char *)malloc(sizeof(char) * len + 1);
	if (ris == NULL)
		return (NULL);
	ris[len] = '\0';
	if (n < 0)
		ris[0] = '-';
	if (n == 0)
		ris[0] = '0';
	while (n)
	{
		if (n > 0)
			ris[--len] = b[n % 10];
		else
			ris[--len] = b[(n % 10) * -1];
		n /= 10;
	}
	return (ris);
}
