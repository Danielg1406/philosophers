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

typedef struct s_table    t_table;

typedef struct s_philosopher
{
    int             id;
    int             flag_dead;
    int             meals_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_table         *table;
}                   t_philosopher;

typedef struct s_table
{
    int             philos_amount;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             flag_must_eat;
    int             must_eat_rounds;
    int             stop;
    long            start_time;
    t_philosopher   *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t *waiter;
    pthread_mutex_t *print_status;
    int             *queue;
    int             q_head;
    int             q_tail;
    pthread_mutex_t *q_mutex;
}                   t_table;

/* CHECKERS */
int     argument_checker(int argc, char **argv);
int     is_valid_int(char *str);

/* INITIALIZATION */
int     initialize_table(int argc, char **argv, t_table *table);
int     create_philos(t_table *t);

/* UTILS */
int     ft_atol(const char *str);
size_t  ft_strlen(const char *s);
long    now_ms(void);
void    print_status(t_table *table, int id, char *msg);
void    controlled_sleep(void);
void    msleep(long ms, t_table *t);


/* ROUTINES */
void    *philo_routine(void *arg);
void    *monitor_routine(void *arg);

#endif