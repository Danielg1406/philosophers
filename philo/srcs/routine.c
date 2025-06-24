#include "philo.h"

static void	philo_think(t_philosopher *philo)
{
	print_status(philo->table, philo->id, "is thinking");
}

static void	philo_sleep(t_philosopher *philo)
{
	print_status(philo->table, philo->id, "is sleeping");
	msleep(philo->table->time_to_sleep, philo->table);
}

static int	philo_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->table, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->table, philo->id, "has taken a fork");
	}
	philo->last_meal = now_ms();
	print_status(philo->table, philo->id, "is eating");
	msleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->meals_eaten++;
	if (philo->table->flag_must_eat
		&& (philo->meals_eaten >= philo->table->must_eat_rounds))
		return (1);
	return (0);
}

// TODO: Handle one philo 
void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		msleep(table->time_to_eat, table);
	while (!table->flag_dead)
	{
		philo_think(philo);
		if (philo_eat(philo))
			break ;
		philo_sleep(philo);
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
