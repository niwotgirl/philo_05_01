/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelkis <aabelkis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:51:50 by aabelkis          #+#    #+#             */
/*   Updated: 2026/01/06 14:46:57 by aabelkis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*Print buffered status change if present. 
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

Print elapsed time and philosopher id prefix. 
void	print_timestamped_id(t_monitor_vars *vars)
{
	printf("%ld %d ", vars->now - vars->monitor->start_time_ms, vars->p->id);
}

 Detect starvation for current philosopher; mark death once.
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
*/

/*****/
//this is the new version
/* Print buffered status change if present. */
/*void	print_philo_status(t_monitor_vars *vars)
{
	if (!vars->new_status)
		return ;
	pthread_mutex_lock(&vars->monitor->print_mutex);
	printf("%ld %d ", vars->now - vars->monitor->start_time_ms, vars->p->id);
	if (vars->status == 1)
		printf("is eating\n");
	else if (vars->status == 2)
		printf("is sleeping\n");
	else if (vars->status == 3)
		printf("is thinking\n");
	vars->p->has_new_status = 0;
	pthread_mutex_unlock(&vars->monitor->print_mutex);
}*/

/* Print elapsed time and philosopher id prefix. */
void	print_timestamped_id(t_monitor_vars *vars)
{
	printf("%ld %d ", vars->now - vars->monitor->start_time_ms, vars->p->id);
}

/* Detect starvation for current philosopher; mark death once. */
int	check_philo_death(t_monitor_vars *vars)
{
	if (vars->now - vars->last_meal >= vars->p->time_to_die)
	{
		pthread_mutex_lock(&vars->monitor->death_mutex);
		vars->monitor->someone_died = 1;
		pthread_mutex_unlock(&vars->monitor->death_mutex);
		pthread_mutex_lock(&vars->monitor->print_mutex);
		printf("%ld %d died\n",
			vars->now - vars->monitor->start_time_ms, vars->p->id);
		pthread_mutex_unlock(&vars->monitor->print_mutex);
		return (1);
	}
	return (0);
}
