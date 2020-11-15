#include "philo_one.h"

void	action(t_phil *phil, char *act)
{
	pthread_mutex_lock(phil->mutex[1].mutex);
	gettimeofday(&phil->time, NULL);
	write_msg(phil->time.tv_sec - phil->start_time.tv_sec, phil->phil_id, act);
	pthread_mutex_unlock(phil->mutex[1].mutex);
}

void	*dinner(void *argc)
{
	t_phil *phil;
	phil = (t_phil *) argc;

	action(phil, SIT_DOWN);
	while (1)
	{
		action(phil, THINKS);
		usleep(SEC);
		if (phil->time.tv_sec - phil->start_time.tv_sec > 10)
			break;
	}
	return (0);
}