/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:15:31 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 16:07:30 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	allocate_resources(t_simulation *sim)
{
	sim->mutexes = malloc(sizeof(pthread_mutex_t) * sim->n);
	sim->threads = malloc(sizeof(pthread_t) * sim->n);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->n);
	sim->args_array = malloc(sizeof(t_thread_args *) * sim->n);
	sim->meal_count_mutex = malloc(sizeof(pthread_mutex_t) * sim->n);
	sim->last_meal_time_mutex = malloc(sizeof(pthread_mutex_t) * sim->n);
	if (!sim->threads || !sim->mutexes || !sim->forks || !sim->args_array
		|| !sim->meal_count_mutex || !sim->last_meal_time_mutex)
		return (0);
	sim->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!sim->print_mutex)
		return (0);
	return (1);
}

static void	free_args_array(t_simulation *sim)
{
	int	i;

	if (sim->args_array)
	{
		i = 0;
		while (i < sim->n)
		{
			free(sim->args_array[i]);
			i++;
		}
		free(sim->args_array);
	}
}

static void	destroy_and_free_mutex_array(pthread_mutex_t *mutex_array, int n)
{
	int	i;

	if (mutex_array)
	{
		i = 0;
		while (i < n)
			pthread_mutex_destroy(&mutex_array[i++]);
		free(mutex_array);
	}
}

void	free_resources(t_simulation *sim)
{
	free_args_array(sim);
	destroy_and_free_mutex_array(sim->mutexes, sim->n);
	destroy_and_free_mutex_array(sim->forks, sim->n);
	destroy_and_free_mutex_array(sim->meal_count_mutex, sim->n);
	destroy_and_free_mutex_array(sim->last_meal_time_mutex, sim->n);
	if (sim->print_mutex)
	{
		pthread_mutex_destroy(sim->print_mutex);
		free(sim->print_mutex);
	}
	free(sim->threads);
}
