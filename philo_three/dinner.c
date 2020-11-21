#include "philo_three.h"

/*
** green eat 1 || white sleep 2 || MAGENTA take fork 3
** || CYAN drop fork 4|| Bold Yellow every eat 0 || Bold Red died -1
*/

void	action(t_phil *phil, char *act, t_colour color)
{
	sem_wait(g_semaphore_msg);
	gettimeofday(&phil->time, NULL);
	if (color == Green)
		ft_putstr(GREEN);
	else if (color == White)
		ft_putstr(WHITE);
	else if (color == Magenta)
		ft_putstr(MAGENTA);
	else if (color == Cyan)
		ft_putstr(CYAN);
	else if (color == BoldYellow)
		ft_putstr(BOLDYELLOW);
	else if (color == Bolded)
		ft_putstr(BOLDRED);
	phil_full_msg(get_time(phil->start_time, phil->time), phil->phil_id, act);
	ft_putstr(RESET);
	sem_post(g_semaphore_msg);
}

void	phil_take_fork(t_phil *phil)
{
	sem_wait(g_semaphore);
	action(phil, TAKE_LEFT_FORK, Magenta);
	phil->num_fork += 1;
	sem_wait(g_semaphore);
	action(phil, TAKE_RIGHT_FORK, Magenta);
	phil->num_fork += 1;
}

void	phil_eat(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		gettimeofday(&phil->last_eat, NULL);
		action(phil, EAT, Green);
		phil->num_eat++;
		my_usleep(phil->time_to_eat * MIL_SEC_MICRO);
	}
}

void	phil_throw_fork_sleep(t_phil *phil)
{
	if (phil->num_fork == 2)
	{
		sem_post(g_semaphore);
		action(phil, DROPPED_THE_LEFT_FORK, Cyan);
		phil->num_fork -= 1;
		sem_post(g_semaphore);
		action(phil, DROPPED_THE_RIGHT_FORK, Cyan);
		phil->num_fork -= 1;
		action(phil, SLEEP, White);
		my_usleep(phil->time_to_sleep * MIL_SEC_MICRO);
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
		if (phil->num_must_eat == phil->num_eat)
			break;
	}
	return (0);
}