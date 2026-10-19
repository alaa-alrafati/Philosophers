/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalrofat <aalrofat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 12:46:32 by aalrofat          #+#    #+#             */
/*   Updated: 2026/03/04 12:46:32 by aalrofat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	new_usleep(long time_eating_sleeping, t_data *data)
{
	long	start_time;

	start_time = time_in_ms();
	while (time_in_ms() - start_time < time_eating_sleeping)
	{
		if (process_stopped(data))
			return ;
		usleep(500);
	}
}

int	error_msg(char *msg)
{
	int	x;

	x = 0;
	while (msg[x] != '\0')
		x++;
	if (msg != NULL)
		write(2, msg, x);
	return (1);
}

long	ft_atoi2(const char *nptr)
{
	int		x;
	long	fnum;

	x = 0;
	fnum = 0;
	while ((nptr[x] >= 9 && nptr[x] <= 13) || (nptr[x] == 32))
		x++;
	if (nptr[x] == '+')
		x++;
	while (nptr[x] >= 48 && nptr[x] <= 57)
	{
		fnum = fnum * 10 + (nptr[x] - 48);
		x++;
	}
	return (fnum);
}

int	ft_isdigit(char *str)
{
	int	x;

	if (!str || str[0] == '\0')
		return (FALSE);
	x = 0;
	while ((str[x] >= 9 && str[x] <= 13) || (str[x] == 32))
		x++;
	if (str[x] == '+')
		x++;
	if (str[x] == '\0')
		return (FALSE);
	while (str[x] != '\0')
	{
		if (str[x] < '0' || str[x] > '9')
			return (FALSE);
		x++;
	}
	return (TRUE);
}
