/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 16:24:52 by carys             #+#    #+#             */
/*   Updated: 2022/05/23 12:28:17 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_all *all)
{
	int	i;

	i = -1;
	all->forks = malloc(sizeof(pthread_mutex_t) * (all->number_of_philo));
	if (!(all->forks))
	{
		free(all->philo);
		return (-1);
	}
	while (++i < all->number_of_philo)
		pthread_mutex_init(&all->forks[i], NULL);
	all->print = malloc(sizeof(pthread_mutex_t));
	if (!(all->print))
	{
		free(all->philo);
		free(all->forks);
		return (-1);
	}
	pthread_mutex_init(all->print, NULL);
	return (0);
}

static void	init_philo(int argc, t_all *all, char **argv, int i)
{
	while (++i < all->number_of_philo)
	{
		all->philo[i].count = all->number_of_philo;
		all->philo[i].mutex = all->print;
		all->philo[i].poel = 0;
		all->philo[i].died_thread = &all->died_thread;
		all->philo[i].last_eat = all->start_time;
		all->philo[i].start_time = all->start_time;
		all->philo[i].count_eat = 0;
		all->philo[i].time_to_die = ft_atoi(argv[2], 0, 1);
		all->philo[i].time_to_eat = ft_atoi(argv[3], 0, 1);
		all->philo[i].time_to_sleep = ft_atoi(argv[4], 0, 1);
		if (argc == 6)
			all->philo[i].must_eat = ft_atoi(argv[5], 0, 1);
		else
			all->philo[i].must_eat = -1;
		all->philo[i].name = i + 1;
		all->philo[i].left_fork = &all->forks[i];
		if (i == (all->number_of_philo - 1))
			all->philo[i].right_fork = &all->forks[0];
		else
			all->philo[i].right_fork = &all->forks[i + 1];
	}
}

static int	init_thread(t_all *all)
{
	int	i;

	i = 0;
	all->thread = (pthread_t *)malloc(sizeof(pthread_t) * all->number_of_philo);
	if (!(all->thread))
		return (-1);
	while (i < all->number_of_philo)
	{
		if (pthread_create(&all->thread[i], NULL, ph_life, &all->philo[i]) != 0)
			return (-1);
		if (pthread_detach(all->thread[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	init_table(int argc, t_all *all, char **argv)
{
	gettimeofday(&all->start_time, NULL);
	all->number_of_philo = ft_atoi(argv[1], 0, 1);
	all->died_thread = 0;
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->number_of_philo);
	if (!(all->philo))
		return (-1);
	if (init_forks(all) == -1)
		return (-1);
	init_philo(argc, all, argv, -1);
	if (init_thread(all) == -1)
	{
		free(all->philo);
		free(all->forks);
		free(all->print);
		return (-1);
	}
	return (0);
}
