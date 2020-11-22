#include "philo_two.h"

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

	sem_unlink(NAME_SEMAPHORE_MSG);
	g_semaphore_msg = (sem_t*)malloc(sizeof(sem_t));
	g_semaphore_msg = sem_open(NAME_SEMAPHORE_MSG, O_CREAT | O_EXCL, 0644, 1);
	return (SUCCESS);
}

int			ft_sem_init(t_param param)
{
	char	*sem;

	sem_unlink(NAME_SEMAPHORE);
	g_semaphore = (sem_t*)malloc(sizeof(sem_t));
	g_semaphore = sem_open(NAME_SEMAPHORE, O_CREAT | O_EXCL, 0644, param.number_of_philosophers);
	return (ft_sem_init_msg());
}

int	main(int ac, char **av)
{
	t_param param;
	t_phil *phil;

	param_init(&param, ac, av);
	phil = phil_init(param);
	ft_sem_init(param);
	create_thread(phil, param);
	return (0);
}

//ERROR in main
