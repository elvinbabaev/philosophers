#include "philo_one.h"

void	action(t_phil *phil, char *act)
{
	gettimeofday(&phil->time, NULL);
	phil_full_msg(get_time(phil->start_time, phil->time), phil->phil_id, act);
}

void	phil_take_fork(t_phil *phil)
{
	if (phil->phil_id != 1)
	{
		pthread_mutex_lock(phil->mutex[phil->phil_id - 1].mutex);
		action(phil, TAKE_LEFT_FORK);
		phil->num_fork += 1;
		pthread_mutex_lock(phil->mutex[phil->phil_id - 2].mutex);
		action(phil, TAKE_RIGHT_FORK);
		phil->num_fork += 1;
	}
	else
	{
		pthread_mutex_lock(phil->mutex[phil->num_phil - 1].mutex);
		action(phil, TAKE_RIGHT_FORK);
		phil->num_fork += 1;
		pthread_mutex_lock(phil->mutex[phil->phil_id - 1].mutex);
		action(phil, TAKE_LEFT_FORK);
		phil->num_fork += 1;
	}
}

void	phil_eat(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		action(phil, EAT);
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
			action(phil, TAKE_LEFT_FORK);
			phil->num_fork -= 1;
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 2].mutex);
			action(phil, TAKE_RIGHT_FORK);
			phil->num_fork -= 1;
			action(phil, SLEEP);
			my_usleep(phil->time_to_sleep * MIL_SEC_MICRO);
		}
		else
		{
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 1].mutex);
			action(phil, TAKE_RIGHT_FORK);
			phil->num_fork -= 1;
			pthread_mutex_unlock(phil->mutex[phil->num_phil - 1].mutex);
			action(phil, TAKE_LEFT_FORK);
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
	}
	return (0);
}