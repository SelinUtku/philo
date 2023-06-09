/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:18:47 by sutku             #+#    #+#             */
/*   Updated: 2023/05/30 17:13:23 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	int	time;

	pthread_mutex_lock(p->mutex->print_lock);
	if (check_alive(p) == false)
	{
		pthread_mutex_unlock(p->mutex->print_lock);
		return ;
	}	
	time = current_time() - p->start_time;
	printf("[%d] %d %s\n", time, p->p_pid, str);
	pthread_mutex_unlock(p->mutex->print_lock);
}

void	unlock_mutex(t_philo *p)
{
	pthread_mutex_unlock(p->r_fork_m);
	pthread_mutex_unlock(p->l_fork_m);
}

bool	my_malloc_data(t_data *data)
{
	data->arg = malloc(sizeof(t_arg));
	if (!data->arg)
		return (false);
	data->mutex = malloc(sizeof(t_mutex));
	if (!data->mutex)
		return (false);
	return (true);
}
