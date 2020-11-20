#include "philo_three.h"

void		my_usleep(size_t time)
{
	struct timeval stamp;
	size_t start;
	size_t now;
	gettimeofday(&stamp, NULL);
	start = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	now = start;
	while (now - start < time / 1000)
	{
		usleep(100);
		gettimeofday(&stamp, NULL);
		now = stamp.tv_sec * 1000 + stamp.tv_usec / 1000;
	}
}

int		ft_sem_init_msg(void)
{
	char	*sem_msg;

	if (!(sem_msg = ft_strdup(NAME_SEMAPHORE_MSG)))
		return (ERROR);
	sem_unlink(sem_msg);
	g_semaphore_msg = (sem_t*)malloc(sizeof(sem_t));
	g_semaphore_msg = sem_open(sem_msg, O_CREAT | O_EXCL, 0644, 1);
	return (SUCCESS);
}

int			ft_sem_init(t_param param)
{
	char	*sem;

	if (!(sem = ft_strdup(NAME_SEMAPHORE)))
		return (ERROR);
	sem_unlink(sem);
	g_semaphore = (sem_t*)malloc(sizeof(sem_t));
	g_semaphore = sem_open(sem, O_CREAT | O_EXCL, 0644, param.number_of_philosophers);
	return (ft_sem_init_msg());
}

int	main(int ac, char **av)
{
	t_param param;
	t_phil *phil;

	param_init(&param, ac, av);
	phil = phil_init(param);
	ft_sem_init(param);
	phil_fork(param, phil);
	return (0);
}

//ERROR in main