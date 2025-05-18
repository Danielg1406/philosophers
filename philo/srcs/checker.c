/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:01:55 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 20:47:24 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
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
	if (ft_atoi(argv[i]) == 0)
	{
		printf("Error, you need at least one philosopher\n");
		return (0);
	}
	while (i < argc)
	{	
		if (!is_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}


