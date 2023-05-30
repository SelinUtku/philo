/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:04:21 by sutku             #+#    #+#             */
/*   Updated: 2023/05/30 17:25:45 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	even_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg->num_of_phl)
	{
		if (pthread_create(&data->arr_pid[i], \
			NULL, &philo_routine, &data->philos[i]) != 0)
		{
			write(2, "Failed to create threads\n", 25);
			return (false);
		}
		i = i + 2;
	}
	return (true);
}

bool	odd_philos(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->arg->num_of_phl)
	{
		if (pthread_create(&data->arr_pid[i], \
			NULL, &philo_routine, &data->philos[i]) != 0)
		{
			write(2, "Failed to create threads\n", 25);
			return (false);
		}
		i = i + 2;
	}
	return (true);
}

bool	control_ate_enough(t_data *data, int a)
{
	pthread_mutex_lock(data->mutex->l_meal);
	if (data->enough == data->arg->num_of_phl)
	{
		printf("[%ld] all philosophers ate [%d] time\n", \
			current_time() - data->philos[a].start_time, data->philos[a].meal);
		pthread_mutex_unlock(data->mutex->l_meal);
		return (true);
	}
	pthread_mutex_unlock(data->mutex->l_meal);
	return (false);
}

void	control_philos(t_data *data)
{
	int			a;
	long int	time;

	a = 0;
	while (1)
	{
		if (is_dead(&data->philos[a]) == true
			&& data->philos[a].meal != data->arg->num_of_eat)
		{
			pthread_mutex_lock(data->mutex->print_lock);
			time = current_time() - data->philos[a].start_time;
			printf("[%ld] %d is dead\n", time, data->philos[a].p_pid);
			pthread_mutex_lock(data->mutex->alive);
			a = -1;
			while (++a < data->arg->num_of_phl)
				data->philos[a].is_alive = 0;
			pthread_mutex_unlock(data->mutex->alive);
			pthread_mutex_unlock(data->mutex->print_lock);
			break ;
		}
		if (control_ate_enough(data, a) == true)
			break ;
		a++;
		a = a % data->arg->num_of_phl;
	}
}

bool	call_philos(t_data *data)
{
	int	i;

	if (even_philos(data) == false)
		return (false);
	usleep(100);
	if (odd_philos(data) == false)
		return (false);
	control_philos(data);
	i = -1;
	while (++i < data->arg->num_of_phl)
	{
		if (pthread_join(data->arr_pid[i], NULL) != 0)
		{
			write(2, "Failed waiting threads\n", 23);
			return (false);
		}
	}
	return (true);
}
