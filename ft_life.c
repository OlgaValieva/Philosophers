/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 11:55:16 by carys             #+#    #+#             */
/*   Updated: 2022/05/11 13:10:51 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if ((*philo->died_thread) == philo->count)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->mutex);
	printf("%ld %d has taken a fork\n",
		get_time(philo->start_time), philo->name);
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->mutex);
	if ((*philo->died_thread) == philo->count)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->mutex);
	printf("%ld %d has taken a fork\n",
		get_time(philo->start_time), philo->name);
	pthread_mutex_unlock(philo->mutex);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if ((*philo->died_thread) == philo->count)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->mutex);
	printf("%ld %d is eating\n",
		get_time(philo->start_time), philo->name);
	pthread_mutex_unlock(philo->mutex);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_lock(philo->mutex);
	philo->count_eat++;
	pthread_mutex_unlock(philo->mutex);
	my_usleep(philo->time_to_eat);
}

static void	sleeping_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex);
	if ((*philo->died_thread) == philo->count)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->mutex);
	printf("%ld %d is sleeping\n",
		get_time(philo->start_time), philo->name);
	pthread_mutex_unlock(philo->mutex);
	my_usleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->mutex);
	if ((*philo->died_thread) == philo->count)
	{
		pthread_mutex_unlock(philo->mutex);
		return ;
	}
	pthread_mutex_unlock(philo->mutex);
	pthread_mutex_lock(philo->mutex);
	printf("%ld %d is thinking\n",
		get_time(philo->start_time), philo->name);
	pthread_mutex_unlock(philo->mutex);
}

void	*ph_life(void *phill)
{
	t_philo	*philo;

	philo = (t_philo *)phill;
	if (philo->name % 2 != 0 && philo->count != 1)
		usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->mutex);
	while ((philo->count_eat < philo->must_eat) || philo->must_eat == -1)
	{
		pthread_mutex_unlock(philo->mutex);
		take_fork(philo);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleeping_thinking(philo);
	}
	pthread_mutex_unlock(philo->mutex);
	(*philo->died_thread)++;
	philo->poel = 1;
	return (0);
}
