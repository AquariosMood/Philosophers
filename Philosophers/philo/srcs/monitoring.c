/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:21:25 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 15:51:26 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	check_philosopher_death(t_thread_args *arg)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(arg->last_meal_time_mutex);
	elapsed_time = (current_time.tv_sec - arg->last_meal_time.tv_sec) * 1000
		+ (current_time.tv_usec - arg->last_meal_time.tv_usec) / 1000;
	pthread_mutex_unlock(arg->last_meal_time_mutex);
	if (elapsed_time > arg->die_in)
	{
		pthread_mutex_lock(arg->running_mutex);
		*arg->running = false;
		pthread_mutex_unlock(arg->running_mutex);
		pthread_mutex_lock(arg->print_mutex);
		printf(RED "%ld %d died\n" RESET, get_timestamp_in_ms(arg->start_time),
			arg->philo_number);
		pthread_mutex_unlock(arg->print_mutex);
		return (true);
	}
	return (false);
}

static bool	check_philosophers_status(t_thread_args **args_array, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_lock(args_array[i]->running_mutex);
		if (!*args_array[i]->running)
		{
			pthread_mutex_unlock(args_array[i]->running_mutex);
			return (true);
		}
		pthread_mutex_unlock(args_array[i]->running_mutex);
		if (check_philosopher_death(args_array[i]))
			return (true);
		i++;
	}
	return (false);
}

static void	monitor_loop(t_thread_args **args_array, int n)
{
	while (1)
	{
		if (check_philosophers_status(args_array, n))
			return ;
		if (check_all_philosophers_finished(args_array, n))
			return ;
		usleep(1000);
	}
}

void	*monitor_philosophers(void *arg)
{
	t_thread_args	**args_array;
	int				n;

	args_array = (t_thread_args **)arg;
	n = args_array[0]->number_of_philosophers;
	usleep(1000);
	monitor_loop(args_array, n);
	return (NULL);
}
