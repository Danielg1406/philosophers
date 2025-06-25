/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:07:52 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 20:28:46 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		table;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Error, wrong amount of arguments\n");
		return (1);
	}
	if (!argument_checker(argc, argv) || !initialize_table(argc, argv, &table)
		|| !create_philos(&table))
		return (1);
	i = 0;
	while (i < table.philos_amount)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
