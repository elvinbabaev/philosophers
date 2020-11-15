#include "philo_one.h"

void	action(t_phil *phil, char *act)
{
	pthread_mutex_lock(phil->mutex[phil->num_phil].mutex);
	gettimeofday(&phil->time, NULL);
	write_msg(phil->time.tv_sec - phil->start_time.tv_sec, phil->phil_id, act);
	pthread_mutex_unlock(phil->mutex[phil->num_phil].mutex);
}

void	phil_take_fork(t_phil *phil)
{
	if (phil->phil_id != 1)
	{
		pthread_mutex_lock(phil->mutex[phil->phil_id - 2].mutex);
		action(phil, " взял правую вилку\n");
		pthread_mutex_lock(phil->mutex[phil->phil_id - 1].mutex);
		action(phil, " взял левую вилку\n");
		phil->num_fork += 2;
	}
	else
	{
		action(phil, " взял правую вилку\n");
		pthread_mutex_lock(phil->mutex[phil->phil_id - 1].mutex);
		action(phil, " взял левую вилку\n");
		pthread_mutex_lock(phil->mutex[phil->num_phil - 1].mutex);
		phil->num_fork += 2;
	}
}

void	phil_eat(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		action(phil, " Начинает есть\n");
		usleep(phil->time_to_eat * 1000);
	}
}

void	phil_throw_fork_sleep(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		if (phil->phil_id != 1) {
			action(phil, " бросил левую вилку\n");
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 1].mutex);
			action(phil, " бросил правую вилку\n");
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 2].mutex);
			action(phil, " ушел спать\n");
			usleep(phil->time_to_sleep * 1000);
		}
		else
		{
			action(phil, " бросил левую вилку\n");
			pthread_mutex_unlock(phil->mutex[phil->num_phil - 1].mutex);
			action(phil, " бросил правую вилку\n");
			pthread_mutex_unlock(phil->mutex[phil->phil_id - 1].mutex);
			action(phil, " ушел спать\n");
			usleep(phil->time_to_sleep * 1000);
		}
	}
}

void	*dinner(void *argc)
{
	t_phil *phil;
	phil = (t_phil *) argc;

	while (1)
	{
		if (phil->phil_id % 2 == 1)
			usleep(1000);
		phil_take_fork(phil);
		phil_eat(phil);
		phil_throw_fork_sleep(phil);
		if (!phil->die)
			break;
	}
	return (0);
}