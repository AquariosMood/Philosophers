/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_finished.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:20:09 by crios             #+#    #+#             */
/*   Updated: 2025/02/27 18:19:42 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	are_all_philosophers_finished(t_thread_args **args_array, int n)
{
	int		i;
	long	finished;

	i = 0;
	finished = 0;
	while (i < n)
	{
		pthread_mutex_lock(args_array[i]->meal_count_mutex);
		if (args_array[i]->meals_count == args_array[i]->number_of_meals)
			finished++;
		pthread_mutex_unlock(args_array[i]->meal_count_mutex);
		i++;
	}
	return (finished == n);
}

static void	stop_simulation(t_thread_args **args_array, int n)
{
	int	i;

	i = 0;
	pthread_mutex_lock(args_array[0]->print_mutex);
	printf("\nAll philosophers ate\n");
	printf("\n所有哲学家都吃完了\n");
	pthread_mutex_unlock(args_array[0]->print_mutex);
	while (i < n)
	{
		pthread_mutex_lock(args_array[i]->running_mutex);
		*args_array[i]->running = false;
		pthread_mutex_unlock(args_array[i]->running_mutex);
		i++;
	}
}

bool	check_all_philosophers_finished(t_thread_args **args_array, int n)
{
	if (are_all_philosophers_finished(args_array, n))
	{
		stop_simulation(args_array, n);
		return (true);
	}
	return (false);
}
