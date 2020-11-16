#include "philo_one.h"

int		phil_must_eat(t_phil *phil)
{
	int i;

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
	int i;

	i = 0;
	while (i < phil->num_phil)
	{

		if ((((phil[i].last_eat.tv_sec - phil[i].prev_last_eat.tv_sec) * 1000) > phil->time_to_die) &&
		(((phil[i].last_eat.tv_sec - phil[i].start_time.tv_sec) * 1000) > phil->time_to_die))
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
	int i;

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
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int 	create_thread(t_phil *phil, t_param param)
{
	int				i;
	pthread_t		*thr;
	int				id_phil;

	thr = (pthread_t*)malloc(sizeof(pthread_t) * (param.number_of_philosophers));
	i = -1;
	while (++i < param.number_of_philosophers)
		gettimeofday(&phil[i].start_time, NULL);
	i = -1;
	while (++i < param.number_of_philosophers)
	{
		gettimeofday(&phil[i].time, NULL);
		gettimeofday(&phil[i].last_eat, NULL);
		gettimeofday(&phil[i].prev_last_eat, NULL);
		pthread_create(&thr[i], NULL, dinner, &phil[i]);
//		usleep(100);
	}
	if (!(phil_live_check(phil, &id_phil)))
	{
		gettimeofday(&phil->time, NULL);
		phil_full_msg((phil->time.tv_sec - phil->start_time.tv_sec) * 1000, id_phil, DIED);
		return (0);
	}
//	i = -1;
//	while (++i < param.number_of_philosophers)
//		pthread_join(thr[i], NULL);
	return (SUCCESS);
}