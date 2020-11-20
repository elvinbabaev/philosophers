#include "philo_three.h"

size_t		get_time(struct timeval time_old, struct timeval time_new)
{
	return (((size_t)(time_new.tv_sec * 1000) - (size_t)(time_old.tv_sec * 1000) + (size_t)(time_new.tv_usec / 1000) - (size_t)(time_old.tv_usec / 1000)));
}

//static int	wait_status(int status)
//{
//	if (status == -1)
//		return (ERROR);
//	else if (status == END_EAT)
//		return (END_EAT);
//	else if (status == SUCCESS)
//		return (SUCCESS);
//	return (SUCCESS);
//}
//
//
////void	print_int(int a, int b)
////{
////	char *a_str;
////	char *b_str;
////
////	a_str = ft_itoa(a);
////	b_str = ft_itoa(b);
////	a_str = ft_strjoin(a_str, "||");
////	a_str = ft_strjoin(a_str, b_str);
////	a_str = ft_strjoin(a_str, "\n");
////	write(1, a_str, ft_strlen(a_str));
////}

//
//int		looking_after_the_phil(t_phil *phil)
//{
//	struct timeval	present_time;
//
//	while (phil->die)
//	{
//		gettimeofday(&present_time, NULL);
//		if (present_time.tv_sec * 1000 + present_time.tv_usec / 1000
//		- phil->last_eat.tv_sec * 1000 - phil->last_eat.tv_usec / 1000 < 0)
//			continue;
//		else if ((get_time(phil->last_eat, present_time)) > phil->time_to_die
//		&& (phil->num_fork != 2 || (phil->num_fork == 2 && phil->time_to_eat > phil->time_to_die)))
//		{
//			phil->die = 0;
//			sem_wait(g_semaphore_msg);
//			gettimeofday(&present_time, NULL);
//			ft_putstr(RED);
//			phil_full_msg(get_time(phil->start_time, present_time), phil->phil_id, DIED);
//			ft_putstr(RESET);
//			return (ERROR);
//		}
//		else if (phil->num_must_eat == phil->num_eat)
//		{
//			return (SUCCESS);
//		}
//	}
//	return (SUCCESS);
//}

//int		dinner_phil_child(t_phil phil)
//{
//	pthread_t thr;
//
//	gettimeofday(&phil.start_time, NULL);
//	phil.time = phil.start_time;
//	phil.last_eat = phil.start_time;
//	pthread_create(&thr, NULL, dinner, &phil);
//
//	looking_after_the_phil(&phil);
//
//	pthread_join(thr, NULL);
//	if (phil.num_eat == phil.num_must_eat)
//		return (SUCCESS);
//	return (ERROR);
//}
//// ERROR
//
//int		phil_fork(t_param param, t_phil *phil)
//{
//	int		i;
//	pid_t	*phil_pid;
//	int		status;
//	int		j;
//
//	if (!(phil_pid = (pid_t*)malloc(sizeof(pid_t) * param.number_of_philosophers)))
//		return (ERROR);
//	i = 0;
//	while (i < param.number_of_philosophers)
//	{
//		phil_pid[i] = fork();
//		if (phil_pid[i] == 0)
//			exit(dinner_phil_child(phil[i]));
//		else if(phil_pid[i] > 0)
//			i++;
//		else
//			return (ERROR);
//	}
//	j = 0;
//	i = 0;
//	while (1)
//	{
//		waitpid(-1, &status, 0);
//		if (status == 1)
//		{
//			j++;
//		}
//		else if (status == 0)
//		{
//			while (i < phil->num_phil)
//				kill(phil_pid[i++], SIGKILL);
//			return (ERROR);
//		}
//		else
//			exit(-1);
//		if (j == phil->num_phil)
//		{
//			sem_wait(g_semaphore_msg);
//			ft_putstr(EVERYONE_ATE);
//			exit (SUCCESS);
//		}
//	}
//	return (SUCCESS);
//
//}