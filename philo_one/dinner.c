/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:02:55 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 16:02:57 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	action(t_phil *phil, char *act, t_colour color)
{
	pthread_mutex_lock(phil->mutex[phil->num_phil].mutex);
	if (color == Green)
		ft_putstr(GREEN);
	else if (color == White)
		ft_putstr(WHITE);
	else if (color == Magenta)
		ft_putstr(MAGENTA);
	else if (color == Cyan)
		ft_putstr(CYAN);
	else if (color == BoldYellow)
		ft_putstr(BOLDYELLOW);
	else if (color == Bolded)
		ft_putstr(BOLDRED);
	gettimeofday(&phil->time, NULL);
	phil_full_msg(get_time(phil->start_time, phil->time), phil->phil_id, act);
	ft_putstr(RESET);
	pthread_mutex_unlock(phil->mutex[phil->num_phil].mutex);
}

void	phil_take_fork(t_phil *phil)
{
	if (phil->phil_id != 1)
	{
		pthread_mutex_lock(phil->mutex[phil->phil_id - 1].mutex);
		action(phil, TAKE_LEFT_FORK, Magenta);
		phil->num_fork += 1;
		pthread_mutex_lock(phil->mutex[phil->phil_id - 2].mutex);
		action(phil, TAKE_RIGHT_FORK, Magenta);
		phil->num_fork += 1;
	}
	else
	{
		pthread_mutex_lock(phil->mutex[phil->num_phil - 1].mutex);
		action(phil, TAKE_RIGHT_FORK, Magenta);
		phil->num_fork += 1;
		pthread_mutex_lock(phil->mutex[phil->phil_id - 1].mutex);
		action(phil, TAKE_LEFT_FORK, Magenta);
		phil->num_fork += 1;
	}
}

void	phil_eat(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		action(phil, EAT, Green);
		phil->num_eat++;
		gettimeofday(&phil->last_eat, NULL);
		my_usleep(phil->time_to_eat * MIL_SEC_MICRO);
	}
}

void	phil_throw_fork_sleep(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		if (phil->phil_id != 1)
		{
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 1].mutex);
			action(phil, DROPPED_THE_LEFT_FORK, Cyan);
			phil->num_fork -= 1;
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 2].mutex);
			action(phil, DROPPED_THE_RIGHT_FORK, Cyan);
			phil->num_fork -= 1;
			action(phil, SLEEP, White);
			my_usleep(phil->time_to_sleep * MIL_SEC_MICRO);
		}
		else
		{
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 1].mutex);
			action(phil, DROPPED_THE_RIGHT_FORK, Cyan);
			phil->num_fork -= 1;
			pthread_mutex_unlock(phil->mutex[phil->num_phil - 1].mutex);
			action(phil, DROPPED_THE_LEFT_FORK, Cyan);
			phil->num_fork -= 1;
			action(phil, SLEEP, White);
			my_usleep(phil->time_to_sleep * MIL_SEC_MICRO);
		}
	}
}

void	*dinner(void *argc)
{
	t_phil *phil;

	phil = (t_phil *)argc;
	if (phil->phil_id % 2 != 1)
		usleep(100);
	while (1)
	{
		phil_take_fork(phil);
		phil_eat(phil);
		phil_throw_fork_sleep(phil);
		if (!phil->die)
			break ;
	}
	return (0);
}
