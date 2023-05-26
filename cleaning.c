/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:02:30 by sutku             #+#    #+#             */
/*   Updated: 2023/05/26 16:02:58 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(data->mutex->alive);
	free(data->mutex->alive);
	pthread_mutex_destroy(data->mutex->print_lock);
	free(data->mutex->print_lock);
	pthread_mutex_destroy(data->mutex->meal);
	free(data->mutex->meal);
	pthread_mutex_destroy(data->mutex->l_meal);
	free(data->mutex->l_meal);
}

void	free_all(t_data *data)
{
	destroy_mutexes(data);
	free(data->mutex);
	free(data->forks);
	free(data->philos);
	free(data->arr_pid);
	free(data->arg);
	free(data);
}
