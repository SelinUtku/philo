/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:18:47 by sutku             #+#    #+#             */
/*   Updated: 2023/05/16 04:17:23 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	my_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + str[i] - 48;
		i++;
	}
	return (sign * result);
}

long int	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_func(t_philo *p, char *str)
{
	long int	time;

	pthread_mutex_lock(p->mutex->print_lock);
	time = current_time() - p->start_time;
	printf("[%ld] %d %s\n", time, p->philo_pid, str);
	pthread_mutex_unlock(p->mutex->print_lock);
}

void	unlock_mutex(pthread_mutex_t *m1, pthread_mutex_t *m2)
{
	if (m1)
		pthread_mutex_unlock(m1);
	if (m2)
		pthread_mutex_unlock(m2);
}

void	increase_meal(t_philo *p)
{
	pthread_mutex_lock(p->mutex->meal);
	p->meal++;
	pthread_mutex_unlock(p->mutex->meal);
}
