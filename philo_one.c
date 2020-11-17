#include "philo_one.h"

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
	return ;
}

int	main(int ac, char **av)
{
	t_param param;
	t_phil *phil;

	param_init(&param, ac, av);
	phil = phil_init(param);
	create_thread(phil, param);

	return (0);
}
