#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = arg;
	table = philo->table;
	// Stagger even philosophers to reduce contention
	if (philo->id % 2 == 0)
		msleep(table->time_to_eat, table);
	while (!table->flag_dead)
	{
		// Thinking
		print_status(table, philo->id, "is thinking");
		// Pick up forks in odd-even order to prevent deadlock
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_status(table, philo->id, "has taken a fork");
			pthread_mutex_lock(philo->left_fork);
			print_status(table, philo->id, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(table, philo->id, "has taken a fork");
			pthread_mutex_lock(philo->right_fork);
			print_status(table, philo->id, "has taken a fork");
		}
		// Eating
		philo->last_meal = now_ms();
		print_status(table, philo->id, "is eating");
		msleep(table->time_to_eat, table);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		// Count meals and possibly exit
		philo->meals_eaten++;
		if (table->flag_must_eat && philo->meals_eaten >= table->must_eat_rounds)
			break ;
		// Sleeping
		print_status(table, philo->id, "is sleeping");
		msleep(table->time_to_sleep, table);
	}
	return (NULL);
}

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
