#include "philo_two.h"

void	ft_error(char *s)
{
	write(2, s, ft_strlen(s));
}