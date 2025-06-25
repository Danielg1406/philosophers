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
