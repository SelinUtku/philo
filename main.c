/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:13 by sutku             #+#    #+#             */
/*   Updated: 2023/05/25 18:51:39 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_eating(t_philo *p)
{
	pthread_mutex_lock(p->l_fork_m);
	if (check_alive(p) == true)
	{
		print_func(p, "has taken a left fork");
		pthread_mutex_lock(p->r_fork_m);
		if (check_alive(p) == true)
		{
			print_func(p, "has taken a right fork");
			print_func(p, "is eating");
			last_meal(p);
			p->meal++;
			if (ate_enough(p) == true)
				return (unlock_mutex(p), 2);
			my_sleep(p, p->arg->time_to_eat);
			if (check_alive(p) == false)
				return (-1);
			return (unlock_mutex(p), 0);
		}
		else
			return (-1);
	}
	else
		return (pthread_mutex_unlock(p->l_fork_m), -1);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	while (1)
	{
		print_func(p, "is thinking");
		p->val = philo_is_eating(p);
		if (p->val != -1 && p->val != 2)
		{
			print_func(p, "is sleeping");
			my_sleep(p, p->arg->time_to_sleep);
			if (check_alive(p) == false)
				break ;
		}
		else if (p->val == 2)
			break ;
		else
			break ;
	}
	return (NULL);
}

bool	one_philo(t_data *data)
{
	int	cur;

	if (data->arg->num_of_phl == 1)
	{
		cur = current_time();
		printf("[0] 0 is taken left fork\n");
		while (current_time() - cur < data->arg->time_to_die)
			usleep(500);
		printf("[%d] 0 is dead\n", data->arg->time_to_die);
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		cur;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong Argument Number !\n");
		exit(EXIT_FAILURE);
	}
	if (argument_check(argc, argv) == false)
		exit(EXIT_FAILURE);
	data = create_data(argc, argv);
	data->arr_pid = malloc(sizeof(pthread_t) * data->arg->num_of_phl);
	if (one_philo(data) == true)
		return (0);
	call_philos(data);
	free_all(data);
	return (0);
}
