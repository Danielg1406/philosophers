/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:29:20 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/27 13:35:09 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_manage_sign(const char **str_ptr, int *sign)
{
	const char	*str;

	str = *str_ptr;
	*sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*(str + 1) == '+' || *(str + 1) == '-')
			return (0);
		if (*(str + 1) == '0' && *(str + 2) == '\0')
			return (0);
		if (*str == '-')
			*sign = -1;
		str++;
	}
	if (*str == '0' && *(str + 1) != '\0')
		return (0);
	*str_ptr = str;
	return (1);
}

int	ft_atol(const char *str)
{
	int		sign;
	int		digit;
	long	num;

	sign = 1;
	num = 0;
	if (!ft_manage_sign(&str, &sign))
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		digit = *str - '0';
		if (sign == 1 && num > (INT_MAX - digit) / 10)
			return (-1);
		if (sign == -1 && (-(num) < (INT_MIN + digit) / 10))
			return (-1);
		num = num * 10 + digit;
		str++;
	}
	return (num * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	print_status(t_table *table, int id, char *msg)
{
	int	dead;

	pthread_mutex_lock(&table->state_mutex);
	dead = table->flag_dead;
	pthread_mutex_unlock(&table->state_mutex);
	if (dead)
		return ;
	pthread_mutex_lock(&table->print_status);
	printf("%ld %d %s\n", present_ms() - table->start_time, id, msg);
	pthread_mutex_unlock(&table->print_status);
}
