/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:46:22 by aalrofat          #+#    #+#             */
/*   Updated: 2026/03/04 12:46:22 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_in_ms(void)//time since 1970
{
	struct timeval	current_time;
	long			ms_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (-1);
	ms_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (ms_time);
}

int	convert_argv(int argc, char **argv, t_data *data)
{
	data->num_of_philo = ft_atoi2(argv[1]);
	data->time_to_die = ft_atoi2(argv[2]);
	data->time_to_eat = ft_atoi2(argv[3]);
	data->time_to_sleep = ft_atoi2(argv[4]);
	data->start_process = time_in_ms();
	if (data->start_process == -1)
		return (1);
	data->someone_died = 0;
	data->process_stopped = 0;
	if (argc == 6)
		data->num_meals_must_eaten = ft_atoi2(argv[5]);
	else
		data->num_meals_must_eaten = -1;
	return (0);
}

int	check_arg(int argc, char **argv)
{
	int	x;

	x = 1;
	if (argc < 5 || argc > 6)
		return (FALSE);
	while (x < argc)
	{
		if (!ft_isdigit(argv[x]))
			return (FALSE);
		x++;
	}
	return (TRUE);
}

int	init_program(int argc, char **argv, t_data *data)
{
	if (!check_arg(argc, argv))
		return (error_msg("Error: wrong arg\n"));
	if (convert_argv(argc, argv, data) != 0)
		return (error_msg("Error: time in ms failed\n"));
	if (data->num_of_philo <= 0 || data->num_of_philo > INT_MAX
		|| data->time_to_die <= 0 || data->time_to_die > INT_MAX
		|| data->time_to_eat <= 0 || data->time_to_eat > INT_MAX
		|| data->time_to_sleep <= 0 || data->time_to_sleep > INT_MAX
		|| data->num_meals_must_eaten == 0
		|| data->num_meals_must_eaten > INT_MAX)
		return (error_msg("Error: wrong values\n"));
	data->philos = malloc(data->num_of_philo * sizeof(t_philo));
	data->forks = malloc(data->num_of_philo * sizeof(pthread_mutex_t));
	if (!data->philos || !data->forks)
	{
		free(data->philos);
		free(data->forks);
		return (error_msg("Error: malloc failed\n"));
	}
	init_mutex(data);
	init_philo(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_program(argc, argv, &data) != 0)
		return (1);
	if (create_threads(&data) != 0)
	{
		free_all(&data);
		return (error_msg("Error: create threads failed\n"));
	}
	if (join_threads(&data) != 0)
		return (error_msg("Error: join threads failed\n"));
	free_all(&data);
	return (0);
}
