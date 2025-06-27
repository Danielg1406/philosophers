/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:56:30 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/06/25 14:56:32 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_gap(void)
{
	usleep(50);
}

void	go_to_bed(long ms, t_table *t)
{
	long	start;
	int		dead;

	start = present_ms();
	while (1)
	{
		pthread_mutex_lock(&t->state_mutex);
		dead = t->flag_dead;
		pthread_mutex_unlock(&t->state_mutex);
		if (dead || (present_ms() - start >= ms))
			break ;
		sleep_gap();
	}
}

long	present_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
