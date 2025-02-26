/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:55:02 by lukan             #+#    #+#             */
/*   Updated: 2024/12/05 17:50:56 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void readystruct(int ac, char **av, t_first *first)
{
	first->nphilo = ft_atoi(av[1]);
	first->ttdie = ft_atoi(av[2]);
	first->tteat = ft_atoi(av[3]);
	first->ttsleap = ft_atoi(av[4]);
	first->strtme = get_current_time();
	if (ac == 6)
		first->n_o_t_e_p_m_e = ft_atoi(av[5]);
	else
		first->n_o_t_e_p_m_e = -1;
	first->ifdie = 0;
	mallocthreadfirst(first);
	initphilostr(first);
}

void initphilostr(t_first *first)
{
	int	i;
	
	i = 0;
	first->philo = (t_philo *)malloc(sizeof(t_philo) * first->nphilo);
	if (first->philo == NULL)
		exit(ERROR);
	while (i < first->nphilo)
	{
		first->philo[i].id = i + 1;
		first->philo[i].counteat = 0;
		first->philo[i].cktmeat = first->strtme;
		first->philo[i].lfork = &first->thefork[i];
		if (first->nphilo == 1)
			first->philo[i].rfork = NULL;
		else if (i < first->nphilo - 1)
			first->philo[i].rfork = &first->thefork[i + 1];
		else
			first->philo[i].rfork = &first->thefork[0];
		first->philo[i].first = first;
		pthread_mutex_init(&first->philo[i].ckeat, NULL);
		i++;	
	}	
}

void mallocthreadfirst(t_first *first)
{
	int i;
	
	i = 0;
	pthread_mutex_init(&first->ckdie, NULL);
	first->thefork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * first->nphilo);
	if (first->thefork == NULL)
	{
    	fprintf(stderr, "Errore: Allocazione fallita per le forchette.\n");
    	exit(ERROR);
	}
	while (i < first->nphilo)
	{
		pthread_mutex_init(&first->thefork[i], NULL);
		i++;
	}
}