/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:20:39 by lukan             #+#    #+#             */
/*   Updated: 2024/12/12 16:14:39 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int		ft_atoi(const char *str);
int		check(int argc, char **argv);
void	readystruct(int ac, char **av, t_first *first);

// Ingresso principale del programma
int main(int argc, char **argv)
{
	t_first	first;
	

	if (check(argc, argv))
		return(ERROR);
	// TODO: Inizializzazione dei filosofi e avvio dei thread
	readystruct(argc, argv, &first);
	//write(1, "Debug: Starting philosopher threads\n", 36);
	startreading(&first);
	return 0;
}

int	check(int argc, char **argv)
{
	//check generale sulle formalitá
	int i;
	int y;
	
	i = 1;
	y = 0;
	if (argc < 5 || argc > 6)
		return (ERROR);
	while (argv[i])
	{ 
		y = 0;
		while (argv[i][y])
		{
			if (!(argv[i][y] >= '0' && argv[i][y] <= '9'))
				return (ERROR);
			y++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
		str++;
	}
	return ((int)(result * sign));
}
