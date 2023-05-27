/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:12:07 by sutku             #+#    #+#             */
/*   Updated: 2023/05/27 15:54:00 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(t_philo *p)
{
	long int	time;

	time = current_time() - p->start_time;
	pthread_mutex_lock(p->mutex->l_meal);
	if (time - p->last_eat >= p->arg->time_to_die)
	{
		pthread_mutex_unlock(p->mutex->l_meal);
		return (true);
	}
	pthread_mutex_unlock(p->mutex->l_meal);
	return (false);
}

bool	check_alive(t_philo *p)
{
	pthread_mutex_lock(p->mutex->alive);
	if (p->is_alive == 0)
	{
		unlock_mutex(p);
		pthread_mutex_unlock(p->mutex->alive);
		return (false);
	}
	pthread_mutex_unlock(p->mutex->alive);
	return (true);
}

void	last_meal(t_philo *p)
{
	pthread_mutex_lock(p->mutex->l_meal);
	p->last_eat = current_time() - p->start_time;
	pthread_mutex_unlock(p->mutex->l_meal);
}

bool	ate_enough(t_philo *p)
{
	pthread_mutex_lock(p->mutex->l_meal);
	if (p->meal == p->arg->num_of_eat)
	{
		p->data->enough++;
		pthread_mutex_unlock(p->mutex->l_meal);
		return (true);
	}
	pthread_mutex_unlock(p->mutex->l_meal);
	return (false);
}

void	my_sleep(int mil)
{
	long int	cur;

	cur = current_time();
	while (current_time() - cur < mil)
		usleep(500);
}
