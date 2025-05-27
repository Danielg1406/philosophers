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
	philo_table->philos_amount = ft_atoi(argv[1]);
	philo_table->time_to_die = ft_atoi(argv[2]);
	philo_table->time_to_eat = ft_atoi(argv[3]);
	philo_table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo_table->flag_must_eat = 1;
		philo_table->must_eat_rounds = ft_atoi(argv[5]);
	}
	if (philo_table->philos_amount == -1 || philo_table->time_to_die == -1
		|| philo_table->time_to_eat == -1 || philo_table->time_to_sleep == -1)
	{
		printf("Error, input value is bigger than INT_MAX\n");
		return (0);
	}
	return (1);
}

int	initialize_table(int argc, char **argv)
{
	t_table	philo_table;

	if (!parse_input(argc, argv, &philo_table))
		return (0);
	return (1);
}
