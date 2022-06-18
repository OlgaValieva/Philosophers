/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:50:17 by carys             #+#    #+#             */
/*   Updated: 2022/05/23 09:28:06 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	checking_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("wrong number of arguments\n", 2);
		return (-1);
	}
	while (++i < argc)
	{
		if (ft_atoi(argv[i], 0, 1) <= 0)
		{
			ft_putstr_fd("invalid argument\n", 2);
			return (-1);
		}
	}
	return (0);
}

static void	*ft_death_or_life(t_all *all)
{
	int			i;
	long int	time_of_death;

	i = 0;
	usleep(all->philo[0].time_to_die * 1000);
	while (all->died_thread != all->number_of_philo)
	{
		if (all->philo[i].time_to_die < get_time(all->philo[i].last_eat)
			&& all->philo[i].poel == 0)
		{
			pthread_mutex_lock(all->print);
			all->died_thread = all->number_of_philo;
			pthread_mutex_unlock(all->print);
			pthread_mutex_lock(all->print);
			time_of_death = get_time(all->start_time);
			printf("%ld %d died\n", time_of_death, all->philo[i].name);
			break ;
		}
		i++;
		if (i == all->number_of_philo)
			i = 0;
	}
	return (NULL);
}

int	main( int argc, char **argv)
{
	t_all	all;

	if (checking_arg(argc, argv) == -1)
		return (0);
	if (init_table(argc, &all, argv) == -1)
		return (0);
	ft_death_or_life(&all);
	free(all.philo);
	free(all.forks);
	free(all.print);
	free(all.thread);
	ft_putstr_fd("\n", 1);
	if (all.philo->poel != 0)
		ft_putstr_fd("Everyone is alive and happy\n", 1);
	else
		ft_putstr_fd("The end of philo\n", 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
