/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:29:08 by crios             #+#    #+#             */
/*   Updated: 2025/02/28 16:11:49 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	lock_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(second_fork);
}

void	unlock_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

pthread_mutex_t	*select_first_fork(t_thread_args *args)
{
	if (args->philo_number % 2 == 0)
	{
		usleep(1000);
		return (args->right_fork);
	}
	else
	{
		usleep(1000);
		return (args->left_fork);
	}
}

pthread_mutex_t	*select_second_fork(t_thread_args *args)
{
	if (args->philo_number % 2 == 0)
		return (args->left_fork);
	else
		return (args->right_fork);
}
