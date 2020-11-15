#include "philo_one.h"

int	main(int ac, char **av)
{
	t_param param;
	t_phil *phil;

	param_init(&param, ac, av);
	phil = phil_init(param);
	create_thread(phil, param);

	return (0);
}
