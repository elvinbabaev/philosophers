#include "philo_two.h"

static void		printer(char *s)
{
	ft_putstr(s);
}

int				phil_full_msg(int time, int phil, char *msg)
{
	char *full_msg;
	char *time_str;
	char *phil_str;

	if (!(time_str = ft_itoa(time)))
		return (0);
	if (!(phil_str = ft_itoa(phil)))
		return (0);
	if (!(full_msg = strdup("")))
		return (0);
	if (!(full_msg = ft_strjoin(time_str, TAB)))
		return (0);
	if (!(full_msg = ft_strjoin(full_msg, phil_str)))
		return (0);
	if (!(full_msg = ft_strjoin(full_msg, msg)))
		return (0);
	printer(full_msg);
	free(full_msg);
	free(time_str);
	free(phil_str);
	return (1);
}