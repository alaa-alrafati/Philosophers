/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:41:33 by aalrofat          #+#    #+#             */
/*   Updated: 2026/04/11 10:40:27 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	died_from_hunger(t_philo *philos)
{
	long	time_from_last_meal;

	pthread_mutex_lock(&philos->meal_mutex);
	time_from_last_meal = time_in_ms() - philos->last_meal_eaten;
	pthread_mutex_unlock(&philos->meal_mutex);
	if (time_from_last_meal >= philos->data->time_to_die)
	{
		pthread_mutex_lock(&philos->data->logs_mutex);
		pthread_mutex_lock(&philos->data->death_mutex);
		printf("%ld %d died\n", (time_in_ms() - philos->data->start_process),
			philos->id_num);
		philos->data->someone_died = 1;
		pthread_mutex_unlock(&philos->data->logs_mutex);
		pthread_mutex_unlock(&philos->data->death_mutex);
		return (1);
	}
	return (0);
}

static	int	philo_finished_eating(t_philo *philos)
{
	int	finished_eating_or_not;

	finished_eating_or_not = 0;
	if (philos->data->num_meals_must_eaten != -1)
	{
		pthread_mutex_lock(&philos->meal_mutex);
		if (philos->num_meals_eaten >= philos->data->num_meals_must_eaten)
			finished_eating_or_not = 1;
		pthread_mutex_unlock(&philos->meal_mutex);
	}
	return (finished_eating_or_not);
}

static	int	stop_process_if_finished_eating(t_data *data)
{
	usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->death_mutex);
	data->process_stopped = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}

void	*monitor_process(void *d)
{
	t_data	*data;
	int		all_philo_finshed_eating;
	int		x;

	data = (t_data *)d;
	while (!process_stopped(data))
	{
		x = 0;
		all_philo_finshed_eating = 1;
		while (x < data->num_of_philo)
		{
			if (died_from_hunger(&data->philos[x]))
				return (NULL);
			if (!philo_finished_eating(&data->philos[x]))
				all_philo_finshed_eating = 0;
			x++;
		}
		if (all_philo_finshed_eating == 1
			&& stop_process_if_finished_eating(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
