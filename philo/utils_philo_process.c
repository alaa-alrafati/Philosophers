/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:46:52 by aalrofat          #+#    #+#             */
/*   Updated: 2026/03/04 12:46:52 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	print(t_philo *philos, char *msg)
{
	pthread_mutex_lock(&philos->data->logs_mutex);
	if (!process_stopped(philos->data))
	{
		printf("%ld %d %s\n",
			(time_in_ms() - philos->data->start_process), philos->id_num,
			msg);
	}
	pthread_mutex_unlock(&philos->data->logs_mutex);
}

void	one_philo(t_philo *philos)
{
	pthread_mutex_lock(philos->right_fork);
	print(philos, "has taken a fork");
	pthread_mutex_unlock(philos->right_fork);
	usleep(philos->data->time_to_die * 1000);
}

void	start_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->meal_mutex);
	philos->last_meal_eaten = time_in_ms();
	philos->num_meals_eaten++;
	pthread_mutex_unlock(&philos->meal_mutex);
	print(philos, "is eating");
	new_usleep(philos->data->time_to_eat, philos->data);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

void	philo_eating(t_philo *philos)
{
	if (philos->id_num % 2 == 0)
	{
		pthread_mutex_lock(philos->right_fork);
		print(philos, "has taken a fork");
		if (process_stopped(philos->data))
		{
			pthread_mutex_unlock(philos->right_fork);
			return ;
		}
		pthread_mutex_lock(philos->left_fork);
		print(philos, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		print(philos, "has taken a fork");
		if (process_stopped(philos->data))
		{
			pthread_mutex_unlock(philos->left_fork);
			return ;
		}
		pthread_mutex_lock(philos->right_fork);
		print(philos, "has taken a fork");
	}
	start_eating(philos);
}

void	philo_sleeping_thinking(t_philo *philos)
{
	long	time_to_think;

	if (process_stopped(philos->data))
		return ;
	print(philos, "is sleeping");
	new_usleep(philos->data->time_to_sleep, philos->data);
	if (process_stopped(philos->data))
		return ;
	print(philos, "is thinking");
	time_to_think = philos->data->time_to_eat
		* (philos->data->num_of_philo % 2);
	new_usleep(time_to_think, philos->data);
}
