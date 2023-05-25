/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:30:30 by sutku             #+#    #+#             */
/*   Updated: 2023/05/25 18:51:27 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

# define PHILO_NUM "Philosopher number can not be less than 1 !\n"
# define DIGIT "One of the argument is not a number ! \n"
# define POSITIVE "One of the argument is not a positive number !\n"

typedef struct s_arg
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat;
	int	num_of_phl;
}t_arg;

typedef struct s_mutex
{
	pthread_mutex_t	*alive;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*l_meal;
}t_mutex;

struct	s_data;

typedef struct s_philo
{
	int				philo_pid;
	int				meal;
	int				val;
	int				is_alive;
	long int		start_time;
	long int		last_eat;
	pthread_mutex_t	*l_fork_m;
	pthread_mutex_t	*r_fork_m;
	t_arg			*arg;
	t_mutex			*mutex;
	struct s_data	*data;
}t_philo;

typedef struct s_data
{
	pthread_t		*arr_pid;
	pthread_mutex_t	*forks;
	int				enough;
	t_philo			*philos;
	t_philo			*phl;
	t_arg			*arg;
	t_mutex			*mutex;
}t_data;

// creating data
bool		argument_check(int argc, char **argv);
t_data		*create_data(int argc, char **argv);
void		free_all(t_data *data);
// help functions
int			my_atoi(char *str);
long int	current_time(void);
void		print_func(t_philo *p, char *str);
void		unlock_mutex(t_philo *p);
// philo functions
void		*philo_routine(void *arg);
void		call_philos(t_data *data);
// eating functions
void		last_meal(t_philo *p);
bool		ate_enough(t_philo *p);
// death check
bool		is_dead(t_philo *p);
bool		check_alive(t_philo *p);
// sleep
void		my_sleep(t_philo *p, int mil);

#endif