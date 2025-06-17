#include "philo.h"

long now_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_status(t_table *t, int id, char *msg)
{
    pthread_mutex_lock(t->print_status);
    if (!t->stop)
        printf("%ld %d %s\n",
            now_ms() - t->start_time, id, msg);
    pthread_mutex_unlock(t->print_status);
}

void *philo_routine(void *arg)
{
    t_philosopher  *p = arg;
    t_table        *t = p->table;

    while (!t->stop)
    {
        print_status(t, p->id, "is thinking");

        /* 2) queue up for the waiter */
        pthread_mutex_lock(t->q_mutex);
        t->queue[t->q_tail] = p->id;
        t->q_tail = (t->q_tail + 1) % t->philos_amount;
        pthread_mutex_unlock(t->q_mutex);

        /* busy-wait until it’s our turn… */
        while (1)
        {
            pthread_mutex_lock(t->q_mutex);
            if (t->queue[t->q_head] == p->id)
            {
                pthread_mutex_unlock(t->q_mutex);
                pthread_mutex_lock(t->waiter);
                pthread_mutex_lock(t->q_mutex);
                t->q_head = (t->q_head + 1) % t->philos_amount;
                pthread_mutex_unlock(t->q_mutex);
                break;
            }
            pthread_mutex_unlock(t->q_mutex);
            controlled_sleep();
        }

        /* take forks */
        pthread_mutex_lock(p->left_fork);
        print_status(t, p->id, "has taken a fork");
        pthread_mutex_lock(p->right_fork);
        print_status(t, p->id, "has taken a fork");
        pthread_mutex_unlock(t->waiter);

        /* eat for exactly time_to_eat ms */
        p->last_meal = now_ms();
        print_status(t, p->id, "is eating");
        msleep(t->time_to_eat, t);

        pthread_mutex_unlock(p->left_fork);
        pthread_mutex_unlock(p->right_fork);
        p->meals_eaten++;
        if (t->flag_must_eat && p->meals_eaten >= t->must_eat_rounds)
            break;

        /* sleep for exactly time_to_sleep ms */
        print_status(t, p->id, "is sleeping");
        msleep(t->time_to_sleep, t);
    }
    return (NULL);
}

void *monitor_routine(void *arg)
{
    t_table    *t;
    int        i;

    t = arg;
    while (!t->stop)
    {
        i = 0;
        while (i < t->philos_amount)
        {
            if ((now_ms() - t->philos[i].last_meal)
                > t->time_to_die)
            {
                t->stop = 1;
                print_status(t,
                    t->philos[i].id, "died");
                return (NULL);
            }
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}