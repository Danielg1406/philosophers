/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:20 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/06/25 14:56:24 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_think(t_philosopher *philo)
{
	print_status(philo->table, philo->id, "is thinking");
}

static void	philo_sleep(t_philosopher *philo)
{
	print_status(philo->table, philo->id, "is sleeping");
	go_to_bed(philo->table->time_to_sleep, philo->table);
}

static void	philo_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->id, "has taken a fork");
	}
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->last_meal = present_ms();
	pthread_mutex_unlock(&philo->table->state_mutex);
	print_status(philo->table, philo->id, "is eating");
	go_to_bed(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->state_mutex);
}

static void	handle_single_philo(t_philosopher *philo)
{
	print_status(philo->table, philo->id, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->table, philo->id, "has taken a fork");
	go_to_bed(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo->table, philo->id, "died");
	philo->table->flag_dead = 1;
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;
	int				dead;
	int				done;

	philo = arg;
	table = philo->table;
	if (table->philos_amount == 1)
	{
		handle_single_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		go_to_bed(table->time_to_eat, table);
	while (1)
	{
		pthread_mutex_lock(&table->state_mutex);
		dead = table->flag_dead;
		done = table->flag_must_eat && table->flag_all_ate;
		pthread_mutex_unlock(&table->state_mutex);
		if (dead || done)
			break ;
		philo_eat(philo);
		pthread_mutex_lock(&table->state_mutex);
		done = table->flag_must_eat
			&& philo->meals_eaten >= table->must_eat_rounds;
		pthread_mutex_unlock(&table->state_mutex);
		if (done)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
