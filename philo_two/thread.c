#include "philo_two.h"

size_t		get_time(struct timeval time_old, struct timeval time_new)
{
	return (((size_t)(time_new.tv_sec * 1000) - (size_t)(time_old.tv_sec * 1000) + (size_t)(time_new.tv_usec / 1000) - (size_t)(time_old.tv_usec / 1000)));
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

//void	print_int(int a, int b)
//{
//	char *a_str;
//	char *b_str;

//	a_str = ft_itoa(a);
//	b_str = ft_itoa(b);
//	a_str = ft_strjoin(a_str, "||");
//	a_str = ft_strjoin(a_str, b_str);
//	a_str = ft_strjoin(a_str, "\n");
//	write(1, a_str, ft_strlen(a_str));
//}

//

int		phil_live_time(t_phil *phil)
{
	int	i;
	struct timeval	present_time;
	size_t	time_int;

	i = 0;
	while (i < phil->num_phil)
	{
		gettimeofday(&present_time, NULL);
		if (present_time.tv_sec * 1000 + present_time.tv_usec / 1000
		- phil[i].last_eat.tv_sec * 1000 - phil[i].last_eat.tv_usec / 1000 < 0)
			continue;
		time_int = get_time(phil[i].last_eat, present_time);
		if (time_int > phil[i].time_to_die && (phil[i].num_fork != 2 ||
		(phil[i].num_fork == 2 && phil[i].time_to_eat < phil[i].time_to_die)))
		{
//			print_int(time_int, phil[i].time_to_die);
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
		sem_wait(g_semaphore_msg);
		gettimeofday(&phil->time, NULL);
		ft_putstr(RED);
		phil_full_msg(get_time(phil->start_time, phil->time), id_phil, DIED);
		return (ERROR);
	}
	else
	{
		sem_wait(g_semaphore_msg);
		ft_putstr(YELLOW);
		ft_putstr(EVERYONE_ATE);
	}
//	sem_close(g_semaphore);
//	sem_close(g_semaphore_msg);
//	i = -1;
//	while (++i < param.number_of_philosophers)
//		pthread_join(thr[i], NULL);
	return (SUCCESS);
}
