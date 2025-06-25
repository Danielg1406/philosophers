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

void	controlled_sleep(void)
{
	usleep(50);
}

void	msleep(long ms, t_table *t)
{
	long	start;

	start = now_ms();
	while (!t->flag_dead && (now_ms() - start < ms))
		controlled_sleep();
}

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
