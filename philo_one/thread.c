#include "philo_one.h"

size_t		get_time(struct timeval time_old, struct timeval time_new)
{
	return ((size_t)((time_new.tv_sec * 1000) - (time_old.tv_sec * 1000) + (time_new.tv_usec / 1000) - (time_old.tv_usec / 1000)));
}

int		phil_must_eat(t_phil *phil)
{
	int	i;

	i = 0;
	while (i < phil->num_phil)
	{
		if (phil->num_must_eat != phil->num_eat)
			return (0);
		i++;
	}
	return (1);
}

int		phil_live_time(t_phil *phil)
{
	int	i;
	struct timeval	present_time;

	i = 0;
	while (i < phil->num_phil)
	{
		gettimeofday(&present_time, NULL);
		if (get_time(phil[i].last_eat, present_time) > phil[i].time_to_die)
		{
			phil[i].die = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

int		phil_live_check(t_phil *phil, int *id_phil)
{
	int	i;

	i = 0;
	while (1)
	{
		if (phil->num_must_eat != -1 && phil_must_eat(phil))
			return (1);
		phil_live_time(phil);
		i = 0;
		while (i < phil->num_phil)
		{
			if (!phil[i].die)
			{
				*id_phil = i + 1;
				return (ERROR);
			}
			i++;
		}
		usleep(5);
	}
	return (0);
}

int 	create_thread(t_phil *phil, t_param param)
{
	int				i;
	pthread_t		*thr;
	int				id_phil;

	if (!(thr = (pthread_t*)malloc(sizeof(pthread_t) * (param.number_of_philosophers))))
		return (ERROR);
	i = -1;
	while (++i < param.number_of_philosophers)
		gettimeofday(&phil[i].start_time, NULL);
	i = -1;
	while (++i < param.number_of_philosophers)
	{
		phil[i].time = phil[i].start_time;
		phil[i].last_eat = phil[i].start_time;
		pthread_create(&thr[i], NULL, dinner, &phil[i]);
	}
	if (!(phil_live_check(phil, &id_phil)))
	{
		gettimeofday(&phil->time, NULL);
		phil_full_msg(get_time(phil->start_time, phil->time), id_phil, DIED);
		return (ERROR);
	}
	ft_putstr(EVERYONE_ATE);
//	i = -1;
//	while (++i < param.number_of_philosophers)
//		pthread_join(thr[i], NULL);
	return (SUCCESS);
}