/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:07:52 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 20:28:46 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_table *table)
{
	pthread_t	watcher;
	int			i;

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
	if (pthread_create(&watcher, NULL, watcher_routine, table) != 0)
		return (0);
	pthread_detach(watcher);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Error, wrong amount of arguments\n");
		return (1);
	}
	if (!argument_checker(argc, argv) || !initialize_table(argc, argv, &table)
		|| !create_philos(&table))
		return (1);
	i = 0;
	while (i < table.philos_amount)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
