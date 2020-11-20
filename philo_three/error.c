#include "philo_three.h"

void	ft_error(char *s)
{
	write(2, s, ft_strlen(s));
}