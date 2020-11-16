#include "philo_one.h"

void	action(t_phil *phil, char *act)
{
//	pthread_mutex_lock(phil->mutex[phil->num_phil].mutex);
	gettimeofday(&phil->time, NULL);
	phil_full_msg(1000 * (phil->time.tv_sec - phil->start_time.tv_sec), phil->phil_id, act);
//	pthread_mutex_unlock(phil->mutex[phil->num_phil].mutex);
}

//(int)(((phil->time.tv_sec - phil->start_time.tv_sec) * 1000) + (phil->time.tv_usec/10000 - phil->start_time.tv_usec/10000))

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
		phil->prev_last_eat = phil->last_eat;
		gettimeofday(&phil->last_eat, NULL);
		action(phil, EAT);
		phil->num_eat++;
		usleep(phil->time_to_eat * MIL_SEC_MICRO);
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
			usleep(phil->time_to_sleep * MIL_SEC_MICRO);
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
			usleep(phil->time_to_sleep * MIL_SEC_MICRO);
		}
	}
}

void	*dinner(void *argc)
{
	t_phil *phil;
	phil = (t_phil *) argc;

	while (1)
	{
		if (phil->phil_id % 2 != 1)
			usleep(100);
		phil_take_fork(phil);
		phil_eat(phil);
		phil_throw_fork_sleep(phil);
		if (!phil->die)
			break;
	}
	return (0);
}