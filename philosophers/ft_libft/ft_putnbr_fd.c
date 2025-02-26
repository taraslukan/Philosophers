/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlukan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:55:32 by tlukan            #+#    #+#             */
/*   Updated: 2024/02/06 14:55:59 by tlukan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_calcolo_ptnb(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = n * -1;
	}
	ft_calcolo_ptnb(n, fd);
}

static	void	ft_calcolo_ptnb(int n, int fd)
{
	int		b;
	int		i;
	char	c;

	b = 1000000000;
	while (n / b == 0)
		b = b / 10;
	while (b != 1)
	{
		i = n / b;
		c = i + 48;
		write (fd, &c, 1);
		n = n - (i * b);
		b = b / 10;
	}
	if (b == 1)
	{
		c = n + 48;
		write (fd, &c, 1);
	}
}
