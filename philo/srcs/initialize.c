/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:35:37 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/27 13:35:51 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alloc_table(t_table *t)
{
	int	i;

	t->philos = malloc(sizeof(t_philosopher) * t->philos_amount);
	t->forks = malloc(sizeof(pthread_mutex_t) * t->philos_amount);
	t->queue = malloc(sizeof(int) * t->philos_amount);
	t->waiter = malloc(sizeof(pthread_mutex_t));
	t->print_status = malloc(sizeof(pthread_mutex_t));
	t->q_mutex = malloc(sizeof(pthread_mutex_t));
	if (!t->philos || !t->forks || !t->queue
		|| !t->waiter || !t->print_status || !t->q_mutex)
		return (0);
	pthread_mutex_init(t->waiter, NULL);
	pthread_mutex_init(t->print_status, NULL);
	pthread_mutex_init(t->q_mutex, NULL);
	i = 0;
	while (i < t->philos_amount)
	{
		pthread_mutex_init(&t->forks[i], NULL);
		i++;
	}
	t->q_head = 0;
	t->q_tail = 0;
	return (1);
}

int	initialize_table(int argc, char **argv, t_table *t)
{
	t->philos_amount = ft_atol(argv[1]);
	t->time_to_die = ft_atol(argv[2]);
	t->time_to_eat = ft_atol(argv[3]);
	t->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		t->flag_must_eat = 1;
		t->must_eat_rounds = ft_atol(argv[5]);
	}
	else
		t->flag_must_eat = 0;
	if (!argument_checker(argc, argv) || !alloc_table(t))
		return (0);
	t->stop = 0;
	t->start_time = now_ms();
	return (1);
}
