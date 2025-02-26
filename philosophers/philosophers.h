/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukan <lukan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:40:43 by lukan             #+#    #+#             */
/*   Updated: 2024/12/03 16:23:04 by lukan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#define ERROR 1

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philo t_philo;
// Struttura per rappresentare un filosofo
typedef struct s_first {
	t_philo 		*philo;
	int 			nphilo;
	int 			n_o_t_e_p_m_e;
	int 			ttsleap;
	int		 		tteat;
	int 			ttdie;
	int				ifdie;
	size_t			strtme;
	pthread_t		monitor;
	pthread_mutex_t	*thefork;
	pthread_mutex_t	ckdie;
} t_first;

typedef struct s_philo {
	int				id;
	pthread_mutex_t	ckeat;
	pthread_t		thread;
	int				counteat;
	size_t			cktmeat;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	t_first			*first;
} t_philo;


// Funzione principale del filosofo
void	*monitor_routine(void *arg);
void	*strroutin(void *gen);
size_t	get_current_time(void);
void	readystruct(int ac, char **av, t_first *first);
void	initphilostr(t_first *first);
void	mallocthreadfirst(t_first *first);
void	print_action(t_philo *philo, const char *action);
void	startreading(t_first *first);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	print_action(t_philo *philo, const char *action);
void	take_forks(t_philo *philo);
int		ft_atoi(const char *str);
int		check(int argc, char **argv);


#endif