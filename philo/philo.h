/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:46:12 by aalrofat          #+#    #+#             */
/*   Updated: 2026/03/04 12:46:12 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define FALSE 0
# define TRUE 1

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_data			*data;
	int				id_num;
	long			last_meal_eaten;
	int				num_meals_eaten;
}	t_philo;

struct	s_data
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		logs_mutex;
	pthread_t			monitor_thread;
	pthread_mutex_t		death_mutex;
	t_philo				*philos;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_die;
	long				start_process;
	int					num_meals_must_eaten;
	int					num_of_philo;
	int					someone_died;
	int					process_stopped;
};

int		init_program(int argc, char **argv, t_data *data);
int		check_arg(int argc, char **argv);
int		convert_argv(int argc, char **argv, t_data *data);
long	time_in_ms(void);

void	init_mutex(t_data *data);
void	init_philo(t_data *data);
void	free_all(t_data *data);

int		create_threads(t_data *data);
int		join_threads(t_data *data);
void	*philos_process(void *ph);
int		process_stopped(t_data *data);

void	one_philo(t_philo *philos);
void	philo_eating(t_philo *philos);
void	philo_sleeping_thinking(t_philo *philos);

void	*monitor_process(void *d);

int		ft_isdigit(char *str);
long	ft_atoi2(const char *nptr);
int		error_msg(char *msg);
void	new_usleep(long time_eating_sleeping, t_data *data);

#endif
