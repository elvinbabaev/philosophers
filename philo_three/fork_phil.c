/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_phil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:25:48 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 20:25:49 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long long int		get_time(struct timeval time_old, struct timeval time_new)
{
	return (((time_new.tv_sec * 1000) - (time_old.tv_sec * 1000)
	+ (time_new.tv_usec / 1000) - (time_old.tv_usec / 1000)));
}

int					looking_after_the_phil(t_phil *phil)
{
	struct timeval	present_time;
	struct timeval	last_eat;
	long long int	time_int;

	while (1)
	{
		last_eat = phil->last_eat;
		if (gettimeofday(&present_time, NULL) == -1)
			continue;
		time_int = get_time(last_eat, present_time);
		if (time_int == 1000)
			continue;
		if (present_time.tv_sec * 1000 + present_time.tv_usec / 1000
		- last_eat.tv_sec * 1000 - last_eat.tv_usec / 1000 < 0)
			continue;
		if (time_int > phil->time_to_die)
		{
			phil->die = 0;
			return (ERROR);
		}
		else if (phil->num_eat == phil->num_must_eat)
			return (SUCCESS);
	}
	return (SUCCESS);
}

int					dinner_phil_child(t_phil phil)
{
	pthread_t	pthr;
	int			status;

	gettimeofday(&phil.start_time, NULL);
	phil.last_eat = phil.start_time;
	phil.time = phil.start_time;
	pthread_create(&pthr, NULL, dinner, &phil);
	status = looking_after_the_phil(&phil);
	if (phil.num_fork >= 1)
	{
		sem_post(g_semaphore);
		if (phil.num_fork == 2)
			sem_post(g_semaphore);
	}
	if (!status)
	{
		gettimeofday(&phil.time, NULL);
		ft_putstr(BOLDRED);
		sem_wait(g_semaphore_msg);
		phil_full_msg(get_time(phil.start_time, phil.time), phil.phil_id, DIED);//
		exit(ERROR);
	}
	exit(SUCCESS);
}

int					phil_died_or_ate(t_phil *phil,
					int i, int j, pid_t *phil_pid)
{
	int	status;

	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			j++;
			if (j == phil->num_phil)
			{
				sem_wait(g_semaphore_msg);
				ft_putstr(EVERYONE_ATE);
				free(phil_pid);
				return (SUCCESS);
			}
		}
		else
		{
			while (i < phil->num_phil)
				kill(phil_pid[i++], SIGKILL);
			free(phil_pid);
			return (ERROR);
		}
	}
}

int					phil_fork(t_param param, t_phil *phil)
{
	int		i;
	pid_t	*phil_pid;

	if (!(phil_pid = (pid_t*)malloc(sizeof(pid_t)
	* param.number_of_philosophers)))
		return (ERROR);
	i = 0;
	while (i < param.number_of_philosophers)
	{
		phil_pid[i] = fork();
		if (phil_pid[i] == 0)
		{
			sem_wait(g_semaphore_end);
			dinner_phil_child(phil[i]);
		}
		else if (phil_pid[i] > 0)
			i++;
		else
			return (ERROR);
	}
	i = -1;
	while (++i < param.number_of_philosophers)
		sem_post(g_semaphore_end);
	return (phil_died_or_ate(phil, 0, 0, phil_pid));
}
