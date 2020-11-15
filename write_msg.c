#include "philo_one.h"

void	printer(int num, char *s)
{
	ft_putnbr(num);
	ft_putstr(s);
}

void	write_msg(int time, int phil, char *msg)
{
	printer(time, TAB);
	printer(phil, msg);
}