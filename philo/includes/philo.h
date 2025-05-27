/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:09:26 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 20:56:27 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	int				flag_dead;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	t_table			*philo_table;
}					t_philosopher;

typedef struct s_table
{
	int				philos_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				flag_must_eat;
	int				must_eat_rounds;
	t_philosopher	*philos;
	pthread_mutex_t	*waiter;
	pthread_mutex_t	*print_status;
}					t_table;

// CHECKERS
int					argument_checker(int argc, char **argv);
int					is_valid_int(char *str);

// INITIALIZATION
int					initialize_table(int argc, char **argv,
						t_table *philo_table);

// UTILS
int					ft_atol(const char *str);
size_t				ft_strlen(const char *s);

#endif
