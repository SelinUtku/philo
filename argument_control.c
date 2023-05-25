/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sutku <sutku@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:05:14 by sutku             #+#    #+#             */
/*   Updated: 2023/05/25 18:23:29 by sutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	my_is_digit(char *str)
{
	int	i;
	int	control;

	i = 0;
	control = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		control = 1;
		i++;
	}
	if (control == 0)
		return (-1);
	return (0);
}

bool	argument_check(int argc, char **argv)
{
	int	i;

	i = 0;
	if (my_atoi(argv[1]) == 0)
	{
		printf(PHILO_NUM);
		return (false);
	}
	while (++i < argc)
	{
		if (my_is_digit(argv[i]) == -1)
		{
			printf(DIGIT);
			return (false);
		}
		if (my_atoi(argv[i]) < 0)
		{
			printf(POSITIVE);
			return (false);
		}
	}
	return (true);
}