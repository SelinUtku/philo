/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:13 by sutku             #+#    #+#             */
/*   Updated: 2023/05/16 20:52:00 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_dead(t_philo *p)
{
	long int	time;

	time = current_time() - p->start_time;
	pthread_mutex_lock(p->mutex->death_lock);
	if (time - p->last_eat > p->arg->time_to_die && p->data->is_dead == 0)
	{
		p->data->is_dead = 1;
		print_func(p, "is dead");
		pthread_mutex_unlock(p->mutex->death_lock);
		return (0);
	}
	pthread_mutex_unlock(p->mutex->death_lock);
	return (1);
}

void	my_sleep(t_philo *p, int mil)
{
	long int	cur;

	cur = current_time();
	while (is_dead(p) == 1 && current_time() - cur < mil)
		usleep(500);
}

int	philo_is_eating(t_philo *p)
{
	pthread_mutex_lock(p->l_fork_m);
	pthread_mutex_lock(p->r_fork_m);
	if (p->data->is_dead != 1 && is_dead(p) == 1)
	{
		print_func(p, "has taken forks");
		print_func(p, "is eating");
		p->last_eat = current_time() - p->start_time;
		my_sleep(p, p->arg->time_to_eat);
		if (p->data->is_dead == 1)
		{
			unlock_mutex(p->r_fork_m, p->l_fork_m);
			return (-1);
		}
		unlock_mutex(p->r_fork_m, p->l_fork_m);
		increase_meal(p);
		return (0);
	}
	else
	{
		unlock_mutex(p->r_fork_m, p->l_fork_m);
		return (-1);
	}
}

void	*philos_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	pthread_mutex_lock(p->mutex->time_lock);
	p->start_time = current_time();
	pthread_mutex_unlock(p->mutex->time_lock);
	while (1)
	{
		print_func(p, "is thinking");
		if (philo_is_eating(p) != -1)
		{
			print_func(p, "is sleeping");
			my_sleep(p, p->arg->time_to_sleep);
			if (p->data->is_dead == 1)
				break ;
		}
		else
			break ;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;
	int		cur;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong Argument !\n");
		exit(EXIT_FAILURE);
	}
	data = create_data(argc, argv);
	data->arr_pid = malloc(sizeof(pthread_t) * data->arg->num_of_phl);
	// if (data->arg->num_of_phl == 1)
	// {
	// 	cur = current_time();
	// 	while (current_time() - cur < data->arg->time_to_die)
	// 		usleep(500);
	// 	printf("[%d] 0 is dead", data->arg->time_to_die);
	// 	return (0);
	// }
	while (i < data->arg->num_of_phl)
	{
		if (pthread_create(&data->arr_pid[i], NULL, &philos_routine, &data->philos[i]) != 0)
		{
			perror("Failed to create threads");
			return (0);
		}
		i = i + 2;
	}
	usleep(100);
	i = 1;
	while (i < data->arg->num_of_phl)
	{
		if (pthread_create(&data->arr_pid[i], NULL, &philos_routine, &data->philos[i]) != 0)
		{
			perror("Failed to create threads");
			return (0);
		}
		i = i + 2;
	}
	i = -1;
	while (++i < data->arg->num_of_phl)
	{
		if (pthread_join(data->arr_pid[i], NULL) != 0)
		{
			perror("Failed waiting threads");
			return (1);
		}
	}
	return (0);
}
