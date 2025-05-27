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

int	parse_input(int argc, char **argv, t_table *philo_table)
{
	philo_table->must_eat_rounds = -2;
	philo_table->flag_must_eat = 0;
	philo_table->philos_amount = ft_atol(argv[1]);
	philo_table->time_to_die = ft_atol(argv[2]);
	philo_table->time_to_eat = ft_atol(argv[3]);
	philo_table->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		philo_table->flag_must_eat = 1;
		philo_table->must_eat_rounds = ft_atol(argv[5]);
	}
	if (philo_table->philos_amount == -1 || philo_table->time_to_die == -1
		|| philo_table->time_to_eat == -1 || philo_table->time_to_sleep == -1
		|| philo_table->must_eat_rounds == -1)
	{
		printf("Error, input value is bigger than INT_MAX\n");
		return (0);
	}
	return (1);
}

int	create_philos(int argc, t_table *philo_table)
{
	return (1);
}

// TODO: Malloc wrapper
int	initialize_table(int argc, char **argv, t_table *philo_table)
{
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*print_status;

	waiter = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	print_status = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(waiter, NULL);
	pthread_mutex_init(print_status, NULL);
	philo_table->waiter = waiter;
	philo_table->print_status = print_status;
	if (!parse_input(argc, argv, philo_table) || !create_philos(argc,
			philo_table))
		return (0);
	return (1);
}
