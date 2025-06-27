/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:59:18 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/06/27 12:59:24 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_single_philo(t_philosopher *philo)
{
	print_status(philo->table, philo->id, "is thinking");
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->table, philo->id, "has taken a fork");
	go_to_bed(philo->table->time_to_die, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	print_status(philo->table, philo->id, "died");
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->table->flag_dead = 1;
	pthread_mutex_unlock(&philo->table->state_mutex);
}
