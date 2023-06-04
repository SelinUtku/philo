/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:02:30 by sutku             #+#    #+#             */
/*   Updated: 2023/06/03 21:55:20 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->arg->num_of_phl)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(data->mutex->alive);
	if (data->mutex->alive)
		free(data->mutex->alive);
	pthread_mutex_destroy(data->mutex->print_lock);
	if (data->mutex->print_lock)
		free(data->mutex->print_lock);
	pthread_mutex_destroy(data->mutex->meal);
	if (data->mutex->meal)
		free(data->mutex->meal);
	pthread_mutex_destroy(data->mutex->l_meal);
	if (data->mutex->l_meal)
		free(data->mutex->l_meal);
}

void	free_all(t_data *data)
{
	destroy_mutexes(data);
	if (data->mutex)
		free(data->mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	if (data->arr_pid)
		free(data->arr_pid);
	if (data->arg)
		free(data->arg);
	if (data)
		free(data);
}
