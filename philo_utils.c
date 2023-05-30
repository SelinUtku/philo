/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:38:29 by sutku             #+#    #+#             */
/*   Updated: 2023/05/30 17:37:09 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*create_forks(int num_philo)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc (sizeof(pthread_mutex_t) * num_philo);
	if (!fork)
		return (NULL);
	i = -1;
	while (++i < num_philo)
		pthread_mutex_init(&fork[i], NULL);
	return (fork);
}

void	init_mutex(t_data *data)
{
	data->mutex->alive = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex->alive, NULL);
	data->mutex->print_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex->print_lock, NULL);
	data->mutex->meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex->meal, NULL);
	data->mutex->l_meal = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->mutex->l_meal, NULL);
}

void	create_data_philo(int i, t_data *data, t_philo *p)
{
	p->data = data;
	p->arg = data->arg;
	p->mutex = data->mutex;
	p->p_pid = i;
	p->is_alive = 1;
	p->meal = 0;
	p->last_eat = 0;
	p->start_time = current_time();
	p->l_fork_m = &data->forks[i];
	if (data->arg->num_of_phl != 1)
		p->r_fork_m = &data->forks[(i + 1) % p->arg->num_of_phl];
	else
		p->r_fork_m = NULL;
}

void	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc (sizeof(t_philo) * data->arg->num_of_phl);
	if (!data->philos)
		return ;
	i = -1;
	while (++i < data->arg->num_of_phl)
		create_data_philo(i, data, &data->philos[i]);
}

t_data	*create_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (my_malloc_data(data) == false)
		return (NULL);
	data->arg->num_of_phl = my_atoi(argv[1]);
	data->arg->time_to_die = my_atoi(argv[2]);
	data->arg->time_to_eat = my_atoi(argv[3]);
	data->arg->time_to_sleep = my_atoi(argv[4]);
	if (argc == 6)
		data->arg->num_of_eat = my_atoi(argv[5]);
	else
		data->arg->num_of_eat = -1;
	data->enough = 0;
	init_mutex(data);
	data->forks = create_forks(data->arg->num_of_phl);
	if (data->forks == NULL)
		return (NULL);
	create_philos(data);
	if (data->philos == NULL)
		return (NULL);
	return (data);
}
