/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:21:25 by carys             #+#    #+#             */
/*   Updated: 2022/05/06 12:11:18 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

int	ft_atoi(const char *str, int i, int minus)
{
	long int	n;

	n = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + minus * (str[i] - '0');
		i++;
		if (minus == 1 && n < 0 && i > 18)
			return (-1);
		else if (minus == -1 && n > 0 && i > 19)
			return (-1);
	}
	if (str[i] != '\0')
		return (-1);
	return (n);
}

static long int	now_time(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000));
}

void	my_usleep(long must_to_be)
{
	long int	start_time;

	start_time = now_time();
	while ((now_time() - start_time) < must_to_be)
		usleep(10);
}

long int	get_time(struct timeval start_time)
{
	struct timeval	tv;
	struct timeval	dif;

	gettimeofday(&tv, NULL);
	dif.tv_sec = tv.tv_sec - start_time.tv_sec;
	dif.tv_usec = tv.tv_usec - start_time.tv_usec;
	return ((dif.tv_sec * 1000) + (dif.tv_usec / 1000));
}
