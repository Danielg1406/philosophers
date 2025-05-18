/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:09:26 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 20:36:47 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_philosopher
{
	int		id;
	int		flag_dead;
	pthread_t	thread;
	pthread_mutex_t	fork;	
}		t_philosopher;

// CHECKERS
int	argument_checker(int argc, char **argv);
int	is_number(char *str);

// UTILS
int	ft_atoi(const char *nptr);

#endif
