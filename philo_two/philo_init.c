#include "philo_two.h"

int		param_init(t_param *param, int ac, char **av)
{
	param->number_of_times_each_philosopher_must_eat = -1;
	if (ac == 5 || ac == 6)
	{
		param->number_of_philosophers = ft_atoi(av[1]);
		param->time_to_die = ft_atoi(av[2]);
		param->time_to_eat = ft_atoi(av[3]);
		param->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			param->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	}
	else
	{
		ft_error("wrong number of arguments\n");
		return (ERROR);
	}
	if (param->number_of_philosophers < 0 || param->time_to_die < 0
	|| param->time_to_eat < 0 || param->time_to_sleep < 0 ||
	(param->number_of_times_each_philosopher_must_eat != -1
	&& param->number_of_times_each_philosopher_must_eat < 0))
		return (ERROR);
	return (SUCCESS);
}

t_phil		*phil_init(t_param param)
{
	t_phil	*phil;
	int		i;
//	t_semaphore	semaphore;
//	char *sem_name;

//	sem_name = ft_strdup("sem");
//	sem_unlink(sem_name);
//	semaphore.semaphore = sem_open(sem_name, O_CREAT | O_EXCL, 0644, param.number_of_philosophers);
	if (!(phil = (t_phil*)malloc(sizeof(t_phil) * param.number_of_philosophers)))
		return (ERROR);
	i = 0;
	while (i < param.number_of_philosophers)
	{
		phil[i].phil_id = i + 1;
		phil[i].time_to_sleep = param.time_to_sleep;
		phil[i].time_to_eat = param.time_to_eat;
		phil[i].time_to_die = param.time_to_die;
		phil[i].die = 1;
		phil[i].num_eat = 0;
		phil[i].num_fork = 0;
		phil[i].num_must_eat = param.number_of_times_each_philosopher_must_eat;
//		phil[i].semaphore = &semaphore;
		phil[i].num_phil = param.number_of_philosophers;
		i++;
	}
	return (phil);
}