/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 10:04:21 by sutku             #+#    #+#             */
/*   Updated: 2023/05/25 18:24:58 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	even_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->arg->num_of_phl)
	{
		if (pthread_create(&data->arr_pid[i], NULL, &philo_routine, &data->philos[i]) != 0)
		{
			perror("Failed to create threads");
			return ;
		}
		i = i + 2;
	}
}

void	odd_philos(t_data *data)
{
	int	i;

	i = 1;
	while (i < data->arg->num_of_phl)
	{
		if (pthread_create(&data->arr_pid[i], NULL, &philo_routine, &data->philos[i]) != 0)
		{
			perror("Failed to create threads");
			return ;
		}
		i = i + 2;
	}
}

bool	control_ate_enough(t_data *data, int a)
{
	pthread_mutex_lock(data->mutex->l_meal);
	if (data->enough == data->arg->num_of_phl)
	{
		printf("[%ld] all philosophers ate [%d] time\n", \
			current_time() - data->philos[a].start_time, data->philos[a].meal);
		pthread_mutex_unlock(data->mutex->l_meal);
		return (false);
	}
	pthread_mutex_unlock(data->mutex->l_meal);
	return (true);
}

void	control_philos(t_data *data)
{
	int	a;
	int	done;
	int	j;

	a = 0;
	done = 0;
	while (done == 0)
	{
		if (is_dead(&data->philos[a]) == true)
		{
			printf("[%ld] %d is dead\n", current_time() - data->philos[a].start_time, data->philos[a].philo_pid);
			j = -1;
			pthread_mutex_lock(data->mutex->alive);
			while (++j < data->arg->num_of_phl)
				data->philos[j].is_alive = 0;
			pthread_mutex_unlock(data->mutex->alive);
			done = 1;
		}
		if (control_ate_enough(data, a) == false)
			break ;
		a++;
		a = a % data->arg->num_of_phl;
	}
}

void	call_philos(t_data *data)
{
	int	i;

	even_philos(data);
	usleep(100);
	odd_philos(data);
	control_philos(data);
	i = -1;
	while (++i < data->arg->num_of_phl)
	{
		if (pthread_join(data->arr_pid[i], NULL) != 0)
		{
			perror("Failed waiting threads");
			return ;
		}
	}
}
