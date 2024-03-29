/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:06:36 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 16:06:38 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			param_init(t_param *param, int ac, char **av)
{
	param->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 5 || ac == 6)
	{
		param->number_of_philosophers = ft_atoi(av[1]);
		param->time_to_die = ft_atoi(av[2]);
		param->time_to_eat = ft_atoi(av[3]);
		param->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			param->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	}
	else
	{
		ft_error(ERROR_ARG);
		return (ERROR);
	}
	if (param->number_of_philosophers <= 0 || param->time_to_die <= 0
	|| param->time_to_eat <= 0 || param->time_to_sleep <= 0 ||
	(param->number_of_times_each_philosopher_must_eat != -1
	&& param->number_of_times_each_philosopher_must_eat <= 0))
	{
		ft_error(ARG_ERROR);
		return (ERROR);
	}
	return (SUCCESS);
}

t_mutex		*mutex_init(t_param param)
{
	t_mutex	*mutex;
	int		j;

	if (!(mutex = (t_mutex*)malloc(sizeof(mutex)
	* (param.number_of_philosophers + 1))))
		return (ERROR);
	j = 0;
	while (j < param.number_of_philosophers)
	{
		if (!(mutex[j].mutex =
		(pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
			return (ERROR);
		pthread_mutex_init(mutex[j].mutex, NULL);
		j++;
	}
	if (!(mutex[j].mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (ERROR);
	pthread_mutex_init(mutex[j].mutex, NULL);
	return (mutex);
}

t_phil		*phil_init(t_param param)
{
	t_phil	*phil;
	int		i;
	t_mutex	*mutex;

	if (!(mutex = mutex_init(param)))
		return (ERROR);
	if (!(phil = (t_phil*)malloc(sizeof(t_phil)
	* param.number_of_philosophers)))
		return (ERROR);
	i = 0;
	while (i < param.number_of_philosophers)
	{
		phil[i].phil_id = i + 1;
		phil[i].time_to_sleep = param.time_to_sleep;
		phil[i].time_to_eat = param.time_to_eat;
		phil[i].time_to_die = param.time_to_die;
		phil[i].die = 1;
		phil[i].num_eat = 0;
		phil[i].num_fork = 0;
		phil[i].num_must_eat = param.number_of_times_each_philosopher_must_eat;
		phil[i].mutex = mutex;
		phil[i].num_phil = param.number_of_philosophers;
		i++;
	}
	return (phil);
}
