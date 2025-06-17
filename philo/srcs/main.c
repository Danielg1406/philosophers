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

int	create_philos(t_table *t)
{
	pthread_t	mon;
	int			i;

	i = 0;
	while (i < t->philos_amount)
	{
		t->philos[i].id = i + 1;
		t->philos[i].table = t;
		t->philos[i].last_meal = t->start_time;
		t->philos[i].meals_eaten = 0;
		t->philos[i].left_fork = &t->forks[i];
		t->philos[i].right_fork = &t->forks[(i + 1) % t->philos_amount];
		if (pthread_create(&t->philos[i].thread, NULL, philo_routine,
				&t->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&mon, NULL, monitor_routine, t) != 0)
		return (0);
	pthread_detach(mon);
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
