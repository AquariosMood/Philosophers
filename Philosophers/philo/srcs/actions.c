/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:11:45 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 16:15:43 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	update_last_meal_time(t_thread_args *args)
{
	pthread_mutex_lock(args->death_mutex);
	pthread_mutex_lock(args->last_meal_time_mutex);
	gettimeofday(&args->last_meal_time, NULL);
	pthread_mutex_unlock(args->last_meal_time_mutex);
	pthread_mutex_unlock(args->death_mutex);
}

void	is_thinking(t_thread_args *args)
{
	pthread_mutex_lock(args->running_mutex);
	if (!*args->running)
	{
		pthread_mutex_unlock(args->running_mutex);
		return ;
	}
	pthread_mutex_unlock(args->running_mutex);
	pthread_mutex_lock(args->print_mutex);
	printf(BLUE "%ld %d is thinking\n" RESET,
		get_timestamp_in_ms(args->start_time), args->philo_number);
	pthread_mutex_unlock(args->print_mutex);
}

bool	handle_forks_and_check_running(t_thread_args *args,
		pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
	*first_fork = select_first_fork(args);
	*second_fork = select_second_fork(args);
	pthread_mutex_lock(args->running_mutex);
	if (!*args->running)
	{
		pthread_mutex_unlock(args->running_mutex);
		return (false);
	}
	pthread_mutex_unlock(args->running_mutex);
	lock_forks(*first_fork, *second_fork);
	pthread_mutex_lock(args->running_mutex);
	if (!*args->running)
	{
		unlock_forks(*first_fork, *second_fork);
		pthread_mutex_unlock(args->running_mutex);
		return (false);
	}
	pthread_mutex_unlock(args->running_mutex);
	return (true);
}

void	time_to_eat(t_thread_args *args)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!handle_forks_and_check_running(args, &first_fork, &second_fork))
		return ;
	pthread_mutex_lock(args->print_mutex);
	pthread_mutex_lock(args->running_mutex);
	if (*args->running)
	{
		printf(WHITE "%ld %d has taken a fork\n" RESET,
			get_timestamp_in_ms(args->start_time), args->philo_number);
		printf(WHITE "%ld %d has taken a fork\n" RESET,
			get_timestamp_in_ms(args->start_time), args->philo_number);
		printf(GREEN "%ld %d is eating\n" RESET,
			get_timestamp_in_ms(args->start_time), args->philo_number);
	}
	pthread_mutex_unlock(args->print_mutex);
	pthread_mutex_unlock(args->running_mutex);
	pthread_mutex_lock(args->meal_count_mutex);
	args->meals_count++;
	pthread_mutex_unlock(args->meal_count_mutex);
	update_last_meal_time(args);
	usleep(args->time_to_eat * 1000);
	unlock_forks(first_fork, second_fork);
}

void	time_to_sleep(t_thread_args *args)
{
	bool	running;

	pthread_mutex_lock(args->running_mutex);
	running = *args->running;
	pthread_mutex_unlock(args->running_mutex);
	if (!running)
		return ;
	pthread_mutex_lock(args->print_mutex);
	printf(YELLOW "%ld %d is sleeping\n" RESET,
		get_timestamp_in_ms(args->start_time), args->philo_number);
	pthread_mutex_unlock(args->print_mutex);
	usleep(args->time_to_sleep * 1000);
}
