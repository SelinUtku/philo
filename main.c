/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:52:13 by sutku             #+#    #+#             */
/*   Updated: 2023/05/30 17:59:04 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_eating(t_philo *p)
{
	pthread_mutex_lock(p->l_fork_m);
	if (check_alive(p) == true)
	{
		print_func(p, "has taken a left fork");
		if (p->arg->num_of_phl == 1)
			return (pthread_mutex_unlock(p->l_fork_m), -1);
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
		if (check_alive(p) == true)
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
		else
			break ;
	}
	return (NULL);
}

void	leaks(void)
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	// atexit(&leaks);
	if (argc != 5 && argc != 6)
	{
		printf("Wrong Argument Number !\n");
		exit(EXIT_FAILURE);
	}
	if (argument_check(argc, argv) == false)
		exit(EXIT_FAILURE);
	data = create_data(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	data->arr_pid = malloc(sizeof(pthread_t) * data->arg->num_of_phl);
	if (!data->arr_pid)
		return (EXIT_FAILURE);
	if (call_philos(data) == false)
		return (EXIT_FAILURE);
	free_all(data);
	return (0);
}
