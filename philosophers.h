/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 22:30:30 by sutku             #+#    #+#             */
/*   Updated: 2023/05/16 17:27:55 by sutku            ###   ########.fr       */
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
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*time_lock;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*run;
}t_mutex;

struct	s_data;

typedef struct s_philo
{
	int				philo_pid;
	bool			eating;
	int				meal;
	long int		start_time;
	long int		last_eat;
	long int		time_stamp;
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
	int				is_dead;
	t_philo			*philos;
	t_philo			*phl;
	t_arg			*arg;
	t_mutex			*mutex;
}t_data;

t_data		*create_data(int argc, char **argv);
int			my_atoi(char *str);
long int	current_time(void);
void		print_func(t_philo *p, char *str);
void		unlock_mutex(pthread_mutex_t *m1, pthread_mutex_t *m2);
void		increase_meal(t_philo *p);

#endif