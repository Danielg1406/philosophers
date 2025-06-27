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

int	create_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_amount)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1)
			% table->philos_amount];
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (0);
		i++;
	}
	if (table->philos_amount > 1)
	{
		if (pthread_create(&table->watcher, NULL, watcher_routine, table) != 0)
			return (0);
	}
	return (1);
}

static int	alloc_table(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philosopher) * table->philos_amount);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_amount);
	if (!table->philos || !table->forks)
		return (0);
	i = 0;
	while (i < table->philos_amount)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&table->print_status, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	initialize_table(int argc, char **argv, t_table *table)
{
	table->philos_amount = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->time_to_think = table->time_to_die - table->time_to_eat
		- table->time_to_sleep;
	if (table->time_to_think < 0)
		table->time_to_think = 0;
	if (argc == 6)
	{
		table->flag_must_eat = 1;
		table->must_eat_rounds = ft_atol(argv[5]);
		table->flag_all_ate = 0;
	}
	else
	{
		table->flag_must_eat = 0;
		table->flag_all_ate = 1;
	}
	if (!argument_checker(argc, argv) || !alloc_table(table))
		return (0);
	table->flag_dead = 0;
	table->start_time = present_ms();
	return (1);
}
