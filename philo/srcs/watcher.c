/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:39 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/06/25 14:57:35 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	must_eat_watcher(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_amount)
	{
		if (table->philos[i].meals_eaten < table->must_eat_rounds)
			return (0);
		i++;
	}
	table->flag_all_ate = 1;
	table->flag_dead = 1;
	return (1);
}

static int	death_watcher(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos_amount)
	{
		if (!(table->flag_must_eat
				&& table->philos[i].meals_eaten >= table->must_eat_rounds))
		{
			if ((present_ms()
					- table->philos[i].last_meal) > table->time_to_die)
			{
				print_status(table, table->philos[i].id, "died");
				table->flag_dead = 1;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	*watcher_routine(void *arg)
{
	t_table	*table;

	table = arg;
	while (!table->flag_dead && !(table->flag_must_eat && table->flag_all_ate))
	{
		if (table->flag_must_eat && must_eat_watcher(table))
			break ;
		if (death_watcher(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
