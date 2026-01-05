/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:01:44 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/05 20:41:43 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Abort if someone died; otherwise prime monitor loop counters/timestamp. */
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

/* Capture current philosopher state under mutex. */
void	snapshot_philo_state(t_monitor_vars *vars)
{
	vars->p = &vars->monitor->philos[vars->i];
	pthread_mutex_lock(&vars->monitor->print_mutex);
	vars->last_meal = vars->p->last_meal_time_ms;
	vars->meals = vars->p->meals_eaten;
	vars->min_meals = vars->p->minimum_meals;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
}

/* Track whether all philosophers met the meal quota. */
void	update_all_done_flag(t_monitor_vars *vars)
{
	if (vars->min_meals == 0 || vars->meals < vars->min_meals)
		vars->all_done = 0;
}

/* Signal termination when everyone is done eating. */
int	handle_all_done(t_monitor_vars *vars)
{
	pthread_mutex_lock(&vars->monitor->print_mutex);
	vars->monitor->someone_died = 1;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
	return (1);
}

/* Monitor thread: watch deaths, print statuses, stop on completion. */
/*void	*monitor_routine(void *arg)
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
			if (handle_all_done(&vars) == 1)
				return (NULL);
		usleep(500);
	}
	return (NULL);
}*/
//new version:
/* Monitor thread: watch deaths, print statuses, stop on completion. */
void	*monitor_routine(void *arg)
{
	t_monitor_vars	vars;
	int				has_meal_limit;

	vars.monitor = (t_monitor *)arg;
	has_meal_limit = (vars.monitor->philos[0].minimum_meals > 0);
	while (1)
	{
		if (check_someone_died_and_init(&vars))
			break ;
		while (vars.i < vars.monitor->num_of_phil)
		{
			snapshot_philo_state(&vars);
			check_philo_death(&vars);
			update_all_done_flag(&vars);
			vars.i++;
		}
		if (vars.all_done && has_meal_limit)
			if (handle_all_done(&vars) == 1)
				return (NULL);
		usleep(100);
	}
	return (NULL);
}