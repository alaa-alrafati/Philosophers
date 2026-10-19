/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:46:39 by aalrofat          #+#    #+#             */
/*   Updated: 2026/03/04 12:46:39 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	stop_process_if_thread_failed(t_data *data, int x)
{
	int	y;

	y = 0;
	pthread_mutex_lock(&(data->death_mutex));
	data->process_stopped = 1;
	pthread_mutex_unlock(&(data->death_mutex));
	while (y < x)
	{
		if (pthread_join(data->philos[y].thread, NULL) != 0)
			return (1);
		y++;
	}
	return (1);
}

int	process_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->death_mutex);
	stopped = data->someone_died || data->process_stopped;
	pthread_mutex_unlock(&data->death_mutex);
	return (stopped);
}

void	*philos_process(void *ph)
{
	t_philo	*philos;

	philos = (t_philo *)ph;
	if (philos->id_num % 2 == 0)
		new_usleep(philos->data->time_to_eat / 2, philos->data);
	if (philos->data->num_of_philo == 1)
	{
		one_philo(philos);
		return (NULL);
	}
	while (!process_stopped(philos->data))
	{
		philo_eating(philos);
		philo_sleeping_thinking(philos);
	}
	return (NULL);
}

int	join_threads(t_data *data)
{
	int	x;
	int	flag;

	flag = 0;
	if (pthread_join(data->monitor_thread, NULL) != 0)
		flag = 1;
	x = 0;
	while (x < data->num_of_philo)
	{
		if (pthread_join(data->philos[x].thread, NULL) != 0)
			flag = 1;
		x++;
	}
	return (flag);
}

int	create_threads(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->num_of_philo)
	{
		if (pthread_create(&data->philos[x].thread, NULL, philos_process,
				&data->philos[x]) != 0)
		{
			return (stop_process_if_thread_failed(data, x));
		}
		x++;
	}
	if (pthread_create(&data->monitor_thread, NULL, monitor_process, data) != 0)
		return (stop_process_if_thread_failed(data, x));
	return (0);
}
