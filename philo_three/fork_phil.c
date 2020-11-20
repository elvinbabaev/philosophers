#include "philo_three.h"

size_t		get_time(struct timeval time_old, struct timeval time_new)
{
	return (((size_t)(time_new.tv_sec * 1000) - (size_t)(time_old.tv_sec * 1000) + (size_t)(time_new.tv_usec / 1000) - (size_t)(time_old.tv_usec / 1000)));
}

int		looking_after_the_phil(t_phil *phil)
{
	struct timeval present_time;

	while (1)
	{
		gettimeofday(&present_time, NULL);
		if (present_time.tv_sec * 1000 + present_time.tv_usec / 1000
		- phil->last_eat.tv_sec * 1000 - phil->last_eat.tv_usec / 1000 < 0)
			continue;
		else if ((get_time(phil->last_eat, present_time)) > phil->time_to_die)
		{
			phil->die = 0;
			printf("%d %d\n", phil->phil_id, 0);				/////???????????
//			phil_full_msg(get_time(phil->start_time, present_time), phil->phil_id, DIED);
			return (ERROR);
		}
		else if (phil->num_eat == phil->num_must_eat)
		{
			printf("%d %d\n", phil->phil_id, 1);				/////???????????
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}

int		dinner_phil_child(t_phil phil)
{
	pthread_t	pthr;
	int			status;

	gettimeofday(&phil.start_time, NULL);
	phil.last_eat = phil.start_time;
	phil.time = phil.start_time;
	pthread_create(&pthr, NULL, dinner, &phil);
	status = looking_after_the_phil(&phil);
	if (!status)
		exit(ERROR);
	exit(SUCCESS);
}

int		phil_fork(t_param param, t_phil *phil)
{
	int		i;
	int		j;
	int		status;
	pid_t	*phil_pid;

	if (!(phil_pid = (pid_t*)malloc(sizeof(pid_t) * param.number_of_philosophers)))
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
	while(++i < param.number_of_philosophers)
		sem_post(g_semaphore_end);
	j = 0;
	i = 0;
	while (1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			j++;
//			write(1, "qwerty\n", 7);
			if (j == phil->num_phil)
			{
				sem_wait(g_semaphore_msg);
				ft_putstr(EVERYONE_ATE);
				exit(SUCCESS);
			}
		}
		else
		{
			while (i < param.number_of_philosophers) {
				kill(phil_pid[i++], SIGKILL);
			}
			return (ERROR);
		}
	}
}