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

static int	alloc_table(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philosopher) * table->philos_amount);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philos_amount);
	table->print_status = malloc(sizeof(pthread_mutex_t));
	if (!table->philos || !table->forks || !table->print_status)
		return (0);
	pthread_mutex_init(table->print_status, NULL);
	i = 0;
	while (i < table->philos_amount)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (1);
}

int	initialize_table(int argc, char **argv, t_table *table)
{
	table->philos_amount = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		table->flag_must_eat = 1;
		table->must_eat_rounds = ft_atol(argv[5]);
	}
	else
		table->flag_must_eat = 0;
	if (!argument_checker(argc, argv) || !alloc_table(table))
		return (0);
	table->flag_dead = 0;
	table->start_time = now_ms();
	return (1);
}
