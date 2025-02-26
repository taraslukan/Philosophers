/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <tlukan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:58:37 by tlukan            #+#    #+#             */
/*   Updated: 2024/06/04 15:32:09 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atoi(const char *str)
{
	size_t			i;
	long int		pon;
	long int		ris;

	ris = 0;
	pon = 1;
	i = 0;
	while (str[i] == ' ' || ((str[i] > 8) && (str[i] < 14)))
		i++;
	if (str[i] == 45)
		pon = -1;
	if (str[i] == 43)
		pon = 1;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		ris = ris * 10 + str[i] - 48;
		i++;
	}
	return (ris * pon);
}
