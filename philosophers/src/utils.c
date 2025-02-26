/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:24:02 by lukan             #+#    #+#             */
/*   Updated: 2024/12/12 16:13:33 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// void	print_action(t_philo *philo, const char *action)
// {
// 	t_first *first = philo->first;

// 	pthread_mutex_lock(&first->ckdie); // Protezione durante la stampa
// 	if (!first->ifdie) // Controlla che nessuno sia morto
// 		printf("%zu %d %s\n", get_current_time() - first->strtme, philo->id + 1, action);
// 	pthread_mutex_unlock(&first->ckdie); // Rilascia il mutex
// }


void	*strroutin(void *gen)
{
	t_philo	*philo;
	t_first	*first;

	philo = (t_philo *)gen;
	first = philo->first;

	while (!first->ifdie) // Il filosofo opera finché nessuno muore
	{
		// 1. Pensare
		print_action(philo, "is thinking");

		// 2. Prendere le forchette
		take_forks(philo);

		// 3. Mangiare
		eat(philo);

		// 4. Rilasciare le forchette
		put_down_forks(philo);

		// 5. Dormire
		print_action(philo, "is sleeping");
		usleep(first->ttsleap * 1000); // Tempo di sonno
	}
	return (NULL); // Terminazione del thread
}

void	startreading(t_first *first)
{
	int	i;

	i = 0;
	while (i < first->nphilo)
	{
		pthread_create(&first->philo[i].thread, NULL, &strroutin, (void *) &first->philo[i]);
		i++;
	}
	pthread_create(&first->monitor, NULL, &monitor_routine, first);
	i = 0;
	while (i < first->nphilo)
	{
		pthread_join(first->philo[i].thread, NULL);
		i++;
	}
	pthread_join(first->monitor, NULL);
}
