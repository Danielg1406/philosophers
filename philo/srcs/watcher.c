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

void	*watcher_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = arg;
	while (!table->flag_dead)
	{
		i = 0;
		while (i < table->philos_amount)
		{
			if ((now_ms() - table->philos[i].last_meal) > table->time_to_die)
			{
				print_status(table, table->philos[i].id, "died");
				table->flag_dead = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
