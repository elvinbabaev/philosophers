/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:19:17 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 16:19:18 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			printer_phil_died(t_phil *phil, int id_phil)
{
	pthread_mutex_lock(phil->mutex[phil->num_phil].mutex);
	ft_putstr(BOLDRED);
	gettimeofday(&phil->time, NULL);
	phil_full_msg(get_time(phil->start_time, phil->time), id_phil, DIED);
	ft_putstr(RESET);
}

void			printer_every_eat(t_phil *phil)
{
	pthread_mutex_lock(phil->mutex[phil->num_phil].mutex);
	ft_putstr(BOLDYELLOW);
	ft_putstr(EVERYONE_ATE);
	ft_putstr(RESET);
}

static void		printer(char *s)
{
	ft_putstr(s);
}

int				phil_full_msg(int time, int phil, char *msg)
{
	char *full_msg;
	char *time_str;
	char *phil_str;
	char *tmp;

	if (!(time_str = ft_itoa(time)))
		return (0);
	if (!(phil_str = ft_itoa(phil)))
		return (0);
	if (!(full_msg = ft_strjoin(time_str, TAB)))
		return (0);
	if (!(tmp = ft_strjoin(full_msg, phil_str)))
		return (0);
	free(full_msg);
	full_msg = tmp;
	if (!(tmp = ft_strjoin(full_msg, msg)))
		return (0);
	free(full_msg);
	full_msg = tmp;
	printer(full_msg);
	free(full_msg);
	free(time_str);
	free(phil_str);
	return (1);
}
