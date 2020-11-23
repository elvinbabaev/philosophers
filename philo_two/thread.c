/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:56:39 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 19:56:40 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int				phil_must_eat(t_phil *phil)
{
	int	i;

	i = 0;
	while (i < phil->num_phil)
	{
		if (phil->num_must_eat != phil->num_eat)
			return (0);
		i++;
	}
	return (1);
}

int				phil_live_time(t_phil *phil)
{
	int				i;
	struct timeval	present_time;
	long long int	time_int;
	struct timeval	last_eat;

	i = 0;
	while (i < phil->num_phil)
	{
		last_eat = phil[i].last_eat;
		if (gettimeofday(&present_time, NULL) == -1)
			continue;
		time_int = get_time(last_eat, present_time);
		if (time_int == 1000)
			continue;
		if (present_time.tv_sec * 1000 + present_time.tv_usec / 1000
		- last_eat.tv_sec * 1000 - last_eat.tv_usec / 1000 < 0)
			continue;
		if (time_int > phil[i].time_to_die)
		{
			phil[i].die = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

int				phil_live_check(t_phil *phil, int *id_phil)
{
	int	i;

	i = 0;
	while (1)
	{
		if (phil->num_must_eat != -1 && phil_must_eat(phil))
			return (1);
		phil_live_time(phil);
		i = 0;
		while (i < phil->num_phil)
		{
			if (!phil[i].die)
			{
				*id_phil = i + 1;
				return (ERROR);
			}
			i++;
		}
	}
	return (0);
}

int				phil_end_msg(t_phil *phil, pthread_t *thr)
{
	int	id_phil;

	id_phil = -1;
	if (!(phil_live_check(phil, &id_phil)))
	{
		sem_wait(g_semaphore_msg);
		gettimeofday(&phil->time, NULL);
		ft_putstr(RED);
		phil_full_msg(get_time(phil->start_time, phil->time), id_phil, DIED);
		free(thr);
		return (ERROR);
	}
	else
	{
		sem_wait(g_semaphore_msg);
		ft_putstr(YELLOW);
		ft_putstr(EVERYONE_ATE);
	}
	return (SUCCESS);
}

int				create_thread(t_phil *phil, t_param param)
{
	int				i;
	pthread_t		*thr;
	int				id_phil;

	if (!(thr = (pthread_t*)malloc(sizeof(pthread_t)
	* (param.number_of_philosophers))))
		return (ERROR);
	i = -1;
	while (++i < param.number_of_philosophers)
		gettimeofday(&phil[i].start_time, NULL);
	i = -1;
	while (++i < param.number_of_philosophers)
	{
		phil[i].time = phil[i].start_time;
		phil[i].last_eat = phil[i].start_time;
		pthread_create(&thr[i], NULL, dinner, &phil[i]);
	}
	return (phil_end_msg(phil, thr));
}
