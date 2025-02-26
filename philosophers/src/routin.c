/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:27 by lukan             #+#    #+#             */
/*   Updated: 2024/12/05 17:29:25 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	if (philo->rfork)
		pthread_mutex_unlock(philo->rfork);
}

void	eat(t_philo *philo)
{
	t_first	*first = philo->first;

	pthread_mutex_lock(&philo->ckeat);
	philo->cktmeat = get_current_time();
	print_action(philo, "is eating");
	pthread_mutex_unlock(&philo->ckeat);
	usleep(first->tteat * 1000);
	philo->counteat++;
	// if (first->n_o_t_e_p_m_e != -1 && philo->counteat >= first->n_o_t_e_p_m_e)
	// {
	// 	//controllo N_O_T_E_P_M_E
	// }
}

void take_forks(t_philo *philo) {
	pthread_mutex_lock(philo->lfork);
	print_action(philo, "has taken a left fork");
	if (philo->rfork)
	{
		if (pthread_mutex_lock(philo->rfork) == 0)
			print_action(philo, "has taken a right fork");
		else
			pthread_mutex_unlock(philo->lfork);
	}
	else
		pthread_mutex_unlock(philo->lfork);
}


void	print_action(t_philo *philo, const char *action)
{
	t_first *first = philo->first;

	pthread_mutex_lock(&first->ckdie); // Protezione durante la stampa
	if (!first->ifdie) // Controlla che nessuno sia morto
		printf("%zu %d %s\n", get_current_time() - first->strtme, philo->id, action);
	pthread_mutex_unlock(&first->ckdie); // Rilascia il mutex
}


// void	*strroutin(void *gen)
// {
// 	t_philo	*philo;
// 	t_first	*first;

// 	philo = (t_philo *)gen;
// 	first = philo->first;

// 	while (!first->ifdie) // Il filosofo opera finché nessuno muore
// 	{
// 		// 1. Pensare
// 		print_action(philo, "is thinking");

// 		// 2. Prendere le forchette
// 		take_forks(philo);

// 		// 3. Mangiare
// 		eat(philo);

// 		// 4. Rilasciare le forchette
// 		put_down_forks(philo);

// 		// 5. Dormire
// 		print_action(philo, "is sleeping");
// 		usleep(first->ttsleap * 1000); // Tempo di sonno
// 	}
// 	return (NULL); // Terminazione del thread
// }