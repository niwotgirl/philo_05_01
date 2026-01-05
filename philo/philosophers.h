/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:59 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/05 20:41:43 by aabelkis         ###   ########.fr       */
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

/*typedef struct s_philo
{
	pthread_mutex_t		*left_fork_mutex;   // set in main
	pthread_mutex_t		right_fork_mutex;  // set in main
	pthread_t			thread;             // philosopher thread
	int					id;                 // philosopher ID
	int					time_to_die;        // constants
	int					time_to_eat;
	int					time_to_sleep;
	int					minimum_meals;
	long				last_meal_time_ms;  // updated in routine
	int					meals_eaten;        // updated in routine
	int					status;             // 1 = eating, 2 = sleeping, 3 = thinking
	int					has_new_status;     // 0 = nothing new, 1 = ready to print
	struct s_monitor	*monitor;          // pointer to monitor for shared data
} t_philo;
*/
typedef struct s_philo
{
	pthread_mutex_t		*left_fork_mutex;
	pthread_mutex_t		right_fork_mutex;
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

/*
typedef struct s_monitor
{
	t_philo			*philos;          // array of philosophers
	int					num_of_phil;     // total number of philosophers
	int					someone_died;    // shared flag (0 = no, 1 = yes)
	long				start_time_ms;   // simulation start time in ms
	pthread_mutex_t		print_mutex;     // mutex to protect printing
	pthread_t			thread;          // monitor thread
} t_monitor;*/
typedef struct s_monitor
{
	t_philo				*philos;
	int					num_of_phil;
	int					someone_died;
	long				start_time_ms;
	pthread_mutex_t		print_mutex;
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

/*
typedef struct s_monitor_vars
{
	t_monitor	*monitor;   // pointer to the monitor struct
	long		now;        // current timestamp
	long		last_meal;  // last meal time for current philosopher
	int			i;          // loop index
	int			status;     // current philosopher status
	int			new_status; // flag if status changed
	int			meals;      // number of meals eaten
	int			min_meals;  // minimum meals required
	t_philo		*p;         // pointer to current philosopher
	int			all_done;   // flag if all philosophers finished
}   t_monitor_vars;
*/

int		handle_single_philosopher(t_monitor *m);
void	init_philosophers(int argc, char **argv, t_monitor *m);
int		validate_and_init(int argc, char **argv, t_monitor *m);
int		ft_error_atoi(const char *nptr);
int		ft_error(char **argv, int i);
//char	*ft_strcpy(char *dest, const char *src);
//char	*ft_strdup(const char *s);
//char	*ft_itoa(int n);
void	*monitor_routine(void *arg);
void	print_philo_status(t_monitor_vars *vars);
int		check_philo_death(t_monitor_vars *vars);
void	print_timestamped_id(t_monitor_vars *vars);
void	*routine(void *arg);
void	custom_sleep(int val);
void	struct_init(int val, int j, int i, t_philo *philo);
//long	timestamp_ms(long start_time_ms);
long	get_current_time_ms(void);
void	pick_up_forks(t_philo *philo);
void	eat(t_philo *philo);
void	release_forks(t_philo *philo);
int		has_finished_meals(t_philo *philo);

#endif
