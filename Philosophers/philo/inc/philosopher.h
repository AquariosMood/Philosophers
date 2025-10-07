/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crios <crios@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:35:12 by crios             #+#    #+#             */
/*   Updated: 2025/02/27 18:07:22 by crios            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_t_thread_args
{
	int				philo_number;
	int				number_of_philosophers;
	int				die_in;

	int				meals_count;
	int				number_of_meals;
	int				time_to_eat;
	int				is_dead;
	int				time_to_sleep;
	struct timeval	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meal_count_mutex;
	pthread_mutex_t	*last_meal_time_mutex;
	pthread_mutex_t	*print_mutex;
	bool			*running;
	pthread_mutex_t	*running_mutex;
	struct timeval	last_meal_time;
}					t_thread_args;

typedef struct s_simulation
{
	int				n;
	t_thread_args	**args_array;
	struct timeval	start_time;
	bool			simulation_running;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	*meal_count_mutex;
	pthread_mutex_t	*last_meal_time_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_t		monitor_thread;
}					t_simulation;

typedef struct s_philo_params
{
	int				number_of_meals;
	int				die_in;
	int				time_to_eat;
	int				time_to_sleep;
}					t_philo_params;

# define RESET "\033[0m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define WHITE "\033[1;37m"

void				*philosophers_routine(void *arg);

// ----------- INIT ----------------
void				initialize_simulation(t_simulation *sim);
int					initialize_mutexes(t_simulation *sim);
int					initialize_philosopher(t_simulation *sim, int i,
						t_philo_params params);
long				get_timestamp_in_ms(struct timeval start_time);
int					setup_philosophers(t_simulation *sim,
						t_philo_params params);

// ----------- START ---------------
void				create_threads(t_simulation *sim);
void				start_simulation(t_simulation *sim);
void				*create_philosophers(int n, t_philo_params params);

// ----------- ACTIONS -------------
void				is_thinking(t_thread_args *args);
void				time_to_eat(t_thread_args *args);
void				time_to_sleep(t_thread_args *args);

// ----------- FORKS ---------------
void				lock_forks(pthread_mutex_t *first_fork,
						pthread_mutex_t *second_fork);
void				unlock_forks(pthread_mutex_t *first_fork,
						pthread_mutex_t *second_fork);
pthread_mutex_t		*select_first_fork(t_thread_args *args);
pthread_mutex_t		*select_second_fork(t_thread_args *args);

// ----------- MONITORING ----------
void				*monitor_philosophers(void *arg);
bool				check_all_philosophers_finished(t_thread_args **args_array,
						int n);

// ----------- MEMORY --------------
int					allocate_resources(t_simulation *sim);
void				free_resources(t_simulation *sim);

// ----------- UTILS ---------------
int					ft_atoi(const char *str);
void				log_action(const char *action, const char *color,
						t_thread_args *args);
int					ft_isdigit(int c);

#endif