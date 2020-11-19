#include "philo_two.h"

size_t		get_time(struct timeval time_old, struct timeval time_new)
{
	return (((size_t)(time_new.tv_sec * 1000) - (size_t)(time_old.tv_sec * 1000) + (size_t)(time_new.tv_usec / 1000) - (size_t)(time_old.tv_usec / 1000)));
}
