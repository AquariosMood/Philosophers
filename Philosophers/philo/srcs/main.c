/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:40:21 by crios             #+#    #+#             */
/*   Updated: 2025/02/24 19:04:43 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_positive_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (ft_atoi(str) > 0);
}

int	is_valid_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: philo number");
		printf(" die_in eat_time");
		printf(" sleep_time [number_of_meals]\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive_integer(argv[i]))
		{
			printf("Error: Arguments must be positive integers.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int				number_of_philosophers;
	t_philo_params	params;

	if (is_valid_input(argc, argv))
	{
		number_of_philosophers = ft_atoi(argv[1]);
		params.die_in = ft_atoi(argv[2]);
		params.time_to_eat = ft_atoi(argv[3]);
		params.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			params.number_of_meals = ft_atoi(argv[5]);
		else
			params.number_of_meals = -1;
		create_philosophers(number_of_philosophers, params);
	}
	return (0);
}
