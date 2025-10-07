/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:19:29 by crios             #+#    #+#             */
/*   Updated: 2025/02/27 15:45:40 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	create_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->n)
	{
		pthread_create(&sim->threads[i], NULL, philosophers_routine,
			sim->args_array[i]);
		i++;
	}
	pthread_create(&sim->monitor_thread, NULL, monitor_philosophers,
		sim->args_array);
	i = 0;
	while (i < sim->n)
		pthread_join(sim->threads[i++], NULL);
	pthread_join(sim->monitor_thread, NULL);
}

void	*create_philosophers(int n, t_philo_params params)
{
	t_simulation	sim;

	sim.n = n;
	initialize_simulation(&sim);
	if (!allocate_resources(&sim))
		return (NULL);
	if (!initialize_mutexes(&sim) || !setup_philosophers(&sim, params))
		return (free_resources(&sim), NULL);
	create_threads(&sim);
	free_resources(&sim);
	pthread_mutex_destroy(&sim.simulation_mutex);
	return (NULL);
}
