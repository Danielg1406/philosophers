/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:01:55 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 20:55:51 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_int(char *str)
{
	if (!*str)
	{
		printf("Error, empty input value\n");
		return (0);
	}
	if (ft_strlen(str) > 10)
	{
		printf("Error, input value bigger than INT_MAX\n");
		return (0);
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
		{
			printf("Error, input only positive numbers\n");
			return (0);
		}
		str++;
	}
	return (1);
}

int	argument_checker(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_int(argv[i]))
		return (0);
		i++;
	}
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) > 200)
	{
		printf("Error, you need at least one philosopher, and maximum 200\n");
		return (0);
	}
	if (argc == 6 && (ft_atoi(argv[5]) == 0))
	{
		printf("Error, you need at least one round\n");
		return (0);
	}
	return (1);
}
