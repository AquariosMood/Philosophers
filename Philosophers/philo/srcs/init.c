/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:39:01 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 16:11:30 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	initialize_simulation(t_simulation *sim)
{
	pthread_mutex_init(&sim->simulation_mutex, NULL);
	sim->simulation_running = true;
	gettimeofday(&sim->start_time, NULL);
}

int	initialize_mutexes(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->n)
	{
		if (pthread_mutex_init(&sim->mutexes[i], NULL) != 0
			|| pthread_mutex_init(&sim->forks[i], NULL) != 0
			|| pthread_mutex_init(&sim->meal_count_mutex[i], NULL) != 0
			|| pthread_mutex_init(&sim->last_meal_time_mutex[i], NULL) != 0)
		{
			while (--i >= 0)
			{
				pthread_mutex_destroy(&sim->mutexes[i]);
				pthread_mutex_destroy(&sim->forks[i]);
				pthread_mutex_destroy(&sim->meal_count_mutex[i]);
				pthread_mutex_destroy(&sim->last_meal_time_mutex[i]);
			}
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(sim->print_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	initialize_philosopher(t_simulation *sim, int i, t_philo_params params)
{
	sim->args_array[i] = malloc(sizeof(t_thread_args));
	if (!sim->args_array[i])
		return (0);
	sim->args_array[i]->philo_number = i + 1;
	sim->args_array[i]->number_of_philosophers = sim->n;
	sim->args_array[i]->die_in = params.die_in;
	sim->args_array[i]->time_to_eat = params.time_to_eat;
	sim->args_array[i]->number_of_meals = params.number_of_meals;
	sim->args_array[i]->meals_count = 0;
	sim->args_array[i]->meal_count_mutex = &sim->meal_count_mutex[i];
	sim->args_array[i]->time_to_sleep = params.time_to_sleep;
	sim->args_array[i]->left_fork = &sim->forks[i];
	sim->args_array[i]->right_fork = &sim->forks[(i + 1) % sim->n];
	sim->args_array[i]->death_mutex = &sim->mutexes[i];
	sim->args_array[i]->start_time = sim->start_time;
	sim->args_array[i]->last_meal_time = sim->start_time;
	sim->args_array[i]->running = &sim->simulation_running;
	sim->args_array[i]->running_mutex = &sim->simulation_mutex;
	sim->args_array[i]->print_mutex = sim->print_mutex;
	sim->args_array[i]->last_meal_time_mutex = &sim->last_meal_time_mutex[i];
	return (1);
}

long	get_timestamp_in_ms(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000);
}

int	setup_philosophers(t_simulation *sim, t_philo_params params)
{
	int	i;

	i = 0;
	while (i < sim->n)
	{
		if (!initialize_philosopher(sim, i, params))
		{
			free_resources(sim);
			return (0);
		}
		i++;
	}
	return (1);
}
