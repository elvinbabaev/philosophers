/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:26:08 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 20:26:09 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
	if (param->number_of_philosophers < 0 || param->time_to_die < 0
	|| param->time_to_eat < 0 || param->time_to_sleep < 0 ||
	(param->number_of_times_each_philosopher_must_eat != -1
	&& param->number_of_times_each_philosopher_must_eat < 0))
		return (ERROR);
	return (SUCCESS);
}

t_phil		*phil_init(t_param param)
{
	t_phil	*phil;
	int		i;

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
		phil[i].num_phil = param.number_of_philosophers;
		i++;
	}
	return (phil);
}
