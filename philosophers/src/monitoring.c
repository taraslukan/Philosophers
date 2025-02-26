/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:00:23 by lukan             #+#    #+#             */
/*   Updated: 2024/12/12 17:49:18 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// void	*monitor_routine(void *arg)
// {
// 	t_first *first;
// 	int		i;

// 	first = (t_first *)arg;
// 	while (!first->ifdie)
// 	{
// 		i = 0;
// 		while (i < first->nphilo)
// 		{
// 			pthread_mutex_lock(&first->philo[i].ckeat);
// 			if (get_current_time() - first->philo[i].cktmeat > (size_t)first->ttdie)
// 			{
// 				print_action(&first->philo[i], "died");
// 				pthread_mutex_lock(&first->ckdie);
// 				first->ifdie = 1;
// 				pthread_mutex_unlock(&first->ckdie);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&first->philo[i].ckeat);
// 			i++;
// 		}
// 		usleep(1000);
// 	}
// 	return (NULL);
// }

// void *monitor_routine(void *arg)
// {
//     t_first *first = (t_first *)arg;
//     int i;
//     int finished_eating;

//     while (!first->ifdie)
//     {
//         i = 0;
//         finished_eating = 0;
//         while (i < first->nphilo)
//         {
//             pthread_mutex_lock(&first->philo[i].ckeat);
//             if (get_current_time() - first->philo[i].cktmeat > (size_t)first->ttdie)
//             {
//                 first->ifdie = 1;
//                 print_action(&first->philo[i], "died");
//             }
//             if (first->n_o_t_e_p_m_e != -1 && first->philo[i].counteat >= first->n_o_t_e_p_m_e)
//                 finished_eating++;
//             pthread_mutex_unlock(&first->philo[i].ckeat);
//             i++;
//         }
//         if (finished_eating == first->nphilo) // Tutti hanno mangiato il numero richiesto di volte
//             first->ifdie = 1;
//         usleep(1000); // Riduce il carico della CPU
//     }
//     return (NULL);
// }

int	check_meals(t_first *first)
{
	int	i;
	int	finished_eating;

	if (first->n_o_t_e_p_m_e == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < first->nphilo)
	{
		pthread_mutex_lock(&first->philo[i].ckeat);
		if (first->philo[i].counteat >= first->n_o_t_e_p_m_e)
		{
			finished_eating++;
		}
		pthread_mutex_unlock(&first->philo[i].ckeat);
		i++;
	}
	if  (finished_eating == first->nphilo)
		print_action(&first->philo[0], "all philosopers are full");	
	return (finished_eating == first->nphilo);
}


int	check_death(t_first *first)
{
	int	i;

	i = 0;
	while (i < first->nphilo)
	{
		pthread_mutex_lock(&first->philo[i].ckeat);
		if (get_current_time() - first->philo[i].cktmeat > 
			(size_t)first->ttdie)
		{
			print_action(&first->philo[i], "died");
			pthread_mutex_unlock(&first->philo[i].ckeat);
			return (1);
		}
		pthread_mutex_unlock(&first->philo[i].ckeat);
		i++;
	}
	return (0);
}


void	*monitor_routine(void *arg)
{
	t_first	*first = (t_first *)arg;

	while (!first->ifdie)
	{
		if (check_death(first) || check_meals(first))
			first->ifdie = 1;
		usleep(1000);
	}
	return (NULL);
}