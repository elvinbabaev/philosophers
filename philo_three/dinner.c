#include "philo_three.h"

void	action(t_phil *phil, char *act)
{
	sem_wait(g_semaphore_msg);
	gettimeofday(&phil->time, NULL);
	phil_full_msg(get_time(phil->start_time, phil->time), phil->phil_id, act);
	sem_post(g_semaphore_msg);
}

void	phil_take_fork(t_phil *phil)
{
	if (phil->phil_id != 1)
	{
		sem_wait(g_semaphore);
		action(phil, TAKE_LEFT_FORK);
		phil->num_fork += 1;
		sem_wait(g_semaphore);
		action(phil, TAKE_RIGHT_FORK);
		phil->num_fork += 1;
	}
	else
	{
		sem_wait(g_semaphore);
		action(phil, TAKE_RIGHT_FORK);
		phil->num_fork += 1;
		sem_wait(g_semaphore);
		action(phil, TAKE_LEFT_FORK);
		phil->num_fork += 1;
	}
}

void	phil_eat(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		gettimeofday(&phil->last_eat, NULL);
		action(phil, EAT);
		phil->num_eat++;
		my_usleep(phil->time_to_eat * MIL_SEC_MICRO);
	}
}

void	phil_throw_fork_sleep(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		if (phil->phil_id != 1)
		{
			sem_post(g_semaphore);
			action(phil, DROPPED_THE_LEFT_FORK);
			phil->num_fork -= 1;
			sem_post(g_semaphore);
			action(phil, DROPPED_THE_RIGHT_FORK);
			phil->num_fork -= 1;
			action(phil, SLEEP);
			my_usleep(phil->time_to_sleep * MIL_SEC_MICRO);
		}
		else
		{
			sem_post(g_semaphore);
			action(phil, DROPPED_THE_RIGHT_FORK);
			phil->num_fork -= 1;
			sem_post(g_semaphore);
			action(phil, DROPPED_THE_LEFT_FORK);
			phil->num_fork -= 1;
			action(phil, SLEEP);
			my_usleep(phil->time_to_sleep * MIL_SEC_MICRO);
		}
	}
}

void	*dinner(void *argc)
{
	t_phil *phil;
	phil = (t_phil *) argc;
	if (phil->phil_id % 2 != 1)
		usleep(100);
	while (1)
	{
		phil_take_fork(phil);
		phil_eat(phil);
		phil_throw_fork_sleep(phil);
		if (!phil->die)
			break;
		if (phil->num_must_eat == phil->num_eat)
			break;
	}
	return (0);
}