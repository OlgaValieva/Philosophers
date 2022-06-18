/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:14:32 by carys             #+#    #+#             */
/*   Updated: 2022/05/23 09:38:49 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				name;
	int				count;
	int				must_eat;
	int				count_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				poel;
	int				*died_thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*mutex;
	struct timeval	last_eat;
	struct timeval	start_time;
}	t_philo;

typedef struct s_all
{
	int				number_of_philo;
	int				died_thread;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	struct timeval	start_time;
}	t_all;

void		*ph_life(void *phil);
void		my_usleep(long must_to_be);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *str, int i, int minus);
int			init_table(int argc, t_all *all, char **argv);
long int	get_time(struct timeval start_time);
#endif
