/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:59 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/06 13:25:41 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_mutex_t		*left_fork_mutex;
	pthread_mutex_t		right_fork_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_t			thread;
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					minimum_meals;
	long				last_meal_time_ms;
	int					meals_eaten;
	struct s_monitor	*monitor;
}	t_philo;

typedef struct s_monitor
{
	t_philo				*philos;
	int					num_of_phil;
	int					someone_died;
	long				start_time_ms;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_t			thread;
}	t_monitor;

typedef struct s_main_vars
{
	t_philo				*philos;
	t_monitor			monitor;
	int					num_of_phil;
}	t_main_vars;

typedef struct s_monitor_vars
{
	t_monitor	*monitor;
	long		now;
	long		last_meal;
	int			i;
	int			status;
	int			new_status;
	int			meals;
	int			min_meals;
	t_philo		*p;
	int			all_done;
}	t_monitor_vars;

int		handle_single_philosopher(t_monitor *m);
void	init_philosophers(int argc, char **argv, t_monitor *m);
int		validate_and_init(int argc, char **argv, t_monitor *m);
int		ft_error_atoi(const char *nptr);
int		ft_error(char **argv, int i);
int		check_philosopher_death(t_monitor_vars *vars);
void	*monitor_routine(void *arg);
int		check_philo_death(t_monitor_vars *vars);
void	print_timestamped_id(t_monitor_vars *vars);
void	*routine(void *arg);
void	custom_sleep(int val);
long	get_current_time_ms(void);
int		pick_up_forks(t_philo *philo);
void	eat(t_philo *philo);
void	release_forks(t_philo *philo);
int		has_finished_meals(t_philo *philo);
long	safe_print(t_philo *philo, char *status);
void	struct_init(int val, int j, int i, t_philo *philo);
int		check_death_flag(t_monitor_vars *vars);
void	init_monitor_loop_vars(t_monitor_vars *vars);

#endif
