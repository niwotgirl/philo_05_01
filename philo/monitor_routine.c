/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:44 by aabelkis          #+#    #+#             */
/*   Updated: 2025/11/24 16:05:49 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	int			someone_died;
	int			all_done;
	long		now;
	int			i;
	t_philo		*p;

	monitor = (t_monitor *)arg;
	while (1)
	{
		pthread_mutex_lock(&monitor->print_mutex);
		someone_died = monitor->someone_died;
		pthread_mutex_unlock(&monitor->print_mutex);
		if (someone_died)
			break ;
		all_done = 1;
		now = get_current_time_ms();
		i = 0;
		while (i < monitor->num_of_phil)
		{
			p = &monitor->philos[i];
			pthread_mutex_lock(&monitor->print_mutex);
			long last_meal = p->last_meal_time_ms;
			int status = p->status;
			int new_status = p->has_new_status;
			int meals = p->meals_eaten;
			int min_meals = p->minimum_meals;
			pthread_mutex_unlock(&monitor->print_mutex);
			// Death check
			if (now - last_meal >= p->time_to_die)
			{
				pthread_mutex_lock(&monitor->print_mutex);
				printf("%ld %d died\n", now - monitor->start_time_ms, p->id);
				monitor->someone_died = 1;
				pthread_mutex_unlock(&monitor->print_mutex);
				return (NULL);
			}
			// Status printing
			if (new_status)
			{
				pthread_mutex_lock(&monitor->print_mutex);
				if (status == 1)
					printf("%ld %d is eating\n", now - monitor->start_time_ms, p->id);
				else if (status == 2)
					printf("%ld %d is sleeping\n", now - monitor->start_time_ms, p->id);
				else if (status == 3)
					printf("%ld %d is thinking\n", now - monitor->start_time_ms, p->id);
				p->has_new_status = 0;
				pthread_mutex_unlock(&monitor->print_mutex);
			}
			// Check if minimum meals requirement is met
			if (min_meals == 0 || meals < min_meals)
				all_done = 0;
			i++;
		}
		if (all_done)
		{
			pthread_mutex_lock(&monitor->print_mutex);
			monitor->someone_died = 1;
			pthread_mutex_unlock(&monitor->print_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}*/

int	check_someone_died_and_init(t_monitor_vars *vars)
{
	int	someone_died;

	pthread_mutex_lock(&vars->monitor->print_mutex);
	someone_died = vars->monitor->someone_died;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
	if (someone_died)
		return (1);
	vars->now = get_current_time_ms();
	vars->i = 0;
	vars->all_done = 1;
	return (0);
}

void	snapshot_philo_state(t_monitor_vars *vars)
{
	vars->p = &vars->monitor->philos[vars->i];
	pthread_mutex_lock(&vars->monitor->print_mutex);
	vars->last_meal = vars->p->last_meal_time_ms;
	vars->status = vars->p->status;
	vars->new_status = vars->p->has_new_status;
	vars->meals = vars->p->meals_eaten;
	vars->min_meals = vars->p->minimum_meals;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
}

void	print_timestamped_id(t_monitor_vars *vars)
{
	printf("%ld %d ", vars->now - vars->monitor->start_time_ms, vars->p->id);
}

int	check_philo_death(t_monitor_vars *vars)
{
	if (vars->now - vars->last_meal >= vars->p->time_to_die)
	{
		pthread_mutex_lock(&vars->monitor->print_mutex);
		print_timestamped_id(vars);
		printf("died\n");
		vars->monitor->someone_died = 1;
		pthread_mutex_unlock(&vars->monitor->print_mutex);
		return (1);
	}
	return (0);
}

void	print_philo_status(t_monitor_vars *vars)
{
	if (!vars->new_status)
		return ;
	pthread_mutex_lock(&vars->monitor->print_mutex);
	print_timestamped_id(vars);
	if (vars->status == 1)
		printf("is eating\n");
	else if (vars->status == 2)
		printf("is sleeping\n");
	else if (vars->status == 3)
		printf("is thinking\n");
	vars->p->has_new_status = 0;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
}

void	update_all_done_flag(t_monitor_vars *vars)
{
	if (vars->min_meals == 0 || vars->meals < vars->min_meals)
		vars->all_done = 0;
}

int	handle_all_done(t_monitor_vars *vars)
{
	pthread_mutex_lock(&vars->monitor->print_mutex);
	vars->monitor->someone_died = 1;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_monitor_vars	vars;

	vars.monitor = (t_monitor *)arg;
	while (1)
	{
		if (check_someone_died_and_init(&vars))
			break ;
		while (vars.i < vars.monitor->num_of_phil)
		{
			snapshot_philo_state(&vars);
			if (check_philo_death(&vars))
				return (NULL);
			if (vars.new_status)
				print_philo_status(&vars);
			update_all_done_flag(&vars);
			vars.i++;
		}
		if (vars.all_done)
			return (handle_all_done(&vars));
		usleep(500);
	}
	return (NULL);
}
