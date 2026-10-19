/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:46:48 by aalrofat          #+#    #+#             */
/*   Updated: 2026/03/04 12:46:48 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->num_of_philo)
	{
		pthread_mutex_init(&data->forks[x], NULL);
		pthread_mutex_init(&data->philos[x].meal_mutex, NULL);
		x++;
	}
	pthread_mutex_init(&data->logs_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
}

void	init_philo(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->num_of_philo)
	{
		data->philos[x].id_num = x + 1;
		data->philos[x].last_meal_eaten = data->start_process;
		data->philos[x].num_meals_eaten = 0;
		data->philos[x].right_fork = &data->forks[x];
		data->philos[x].left_fork = &data->forks[(x - 1 + data->num_of_philo)
			% data->num_of_philo];
		data->philos[x].data = data;
		x++;
	}
}

void	free_all(t_data *data)
{
	int	x;

	x = 0;
	while (x < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[x]);
		pthread_mutex_destroy(&data->philos[x].meal_mutex);
		x++;
	}
	pthread_mutex_destroy(&data->logs_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->philos);
	free(data->forks);
}
