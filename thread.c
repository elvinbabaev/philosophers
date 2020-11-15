#include "philo_one.h"

int 	create_thread(t_phil *phil, t_param param)
{
	int				i;
	pthread_t		*thr;

	thr = (pthread_t*)malloc(sizeof(pthread_t) * (param.number_of_philosophers));
	i = -1;
	while (++i < param.number_of_philosophers)
		gettimeofday(&phil[i].start_time, NULL);
	i = -1;
	while (++i < param.number_of_philosophers)
	{
		gettimeofday(&phil[i].time, NULL);
		pthread_create(&thr[i], NULL, dinner, &phil[i]);
		usleep(100);
	}
	i = -1;
	while (++i < param.number_of_philosophers)
		pthread_join(thr[i], NULL);
	return (SUCCESS);
}