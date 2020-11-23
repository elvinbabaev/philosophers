/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:07:02 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 16:07:03 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		my_usleep(size_t time)
{
	struct timeval	stamp;
	size_t			start;
	size_t			now;

	gettimeofday(&stamp, NULL);
	start = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	now = start;
	while (now - start < time / 1000)
	{
		usleep(100);
		gettimeofday(&stamp, NULL);
		now = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	}
}

int			main(int ac, char **av)
{
	t_param	param;
	t_phil	*phil;

	if (!(param_init(&param, ac, av)))
		return (EXIT_FAILURE);
	if (!(phil = phil_init(param)))
		return (EXIT_FAILURE);
	if (!(create_thread(phil, param, 0)))
		return (EXIT_FAILURE);
	free(phil);
	return (0);
}
