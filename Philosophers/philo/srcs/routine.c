/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:04:40 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 16:11:52 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philosophers_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	if (args->philo_number % 2 == 0)
		usleep(10000);
	while (1)
	{
		pthread_mutex_lock(args->running_mutex);
		if (!*args->running)
			return (pthread_mutex_unlock(args->running_mutex), NULL);
		pthread_mutex_unlock(args->running_mutex);
		if (args->number_of_philosophers == 1)
		{
			usleep(args->die_in * 1000);
			return (NULL);
		}
		time_to_eat(args);
		time_to_sleep(args);
		is_thinking(args);
	}
	return (NULL);
}
