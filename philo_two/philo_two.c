/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 19:56:23 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 19:56:24 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int			ft_sem_init_msg(void)
{
	sem_unlink(NAME_SEMAPHORE_MSG);
	if ((g_semaphore_msg = sem_open(NAME_SEMAPHORE_MSG,
	O_CREAT, 0644, 1)) == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

int			ft_sem_init(t_param param)
{
	sem_unlink(NAME_SEMAPHORE);
	if ((g_semaphore = sem_open(NAME_SEMAPHORE,
	O_CREAT, 0644, param.number_of_philosophers)) == SEM_FAILED)
		return (ERROR);
	return (ft_sem_init_msg());
}

int			main(int ac, char **av)
{
	t_param	param;
	t_phil	*phil;

	g_semaphore_msg = 0x0;
	g_semaphore = 0x0;
	if (!(param_init(&param, ac, av)))
		return (EXIT_FAILURE);
	if (!(phil = phil_init(param)))
		return (EXIT_FAILURE);
	if (!(ft_sem_init(param)))
		return (EXIT_FAILURE);
	if (!(create_thread(phil, param)))
		return (EXIT_FAILURE);
	return (0);
}
