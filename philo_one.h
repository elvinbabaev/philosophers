#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

# define SEC 1000000
# define ERROR 0
# define SUCCESS 1
# define TAB "\t"
# define SIT_DOWN " сел за стол\n"
# define TAKE_FORK " взял вилку"
# define DIED " умер\n"
# define EAT_UP " поел\n"
# define SLEEP " уснул\n"
# define THINKS " думает\n"

typedef struct	s_param
{
	int		number_of_philosophers;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int 	number_of_times_each_philosopher_must_eat;
}				t_param;

typedef struct	s_mutex
{
	pthread_mutex_t *mutex;
}				t_mutex;

typedef struct	s_phil
{
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				num_must_eat;
	int				num_eat;
	int				die;
	int				phil_id;
	int				num_fork;
	struct timeval	time;
	struct timeval	start_time;
	struct s_mutex	*mutex;
	int				num_phil;
}				t_phil;

/*core function*/

void		ft_error(char *s);
int			param_init(t_param *param, int ac, char **av);
t_phil		*phil_init(t_param param);
int			create_thread(t_phil *phil, t_param param);
void		*dinner(void *argc);
void		write_msg(int time, int phil, char *msg);

/*utils function*/

size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		ft_putnbr(int n);
void		ft_putchar(char c);
void		ft_putstr(const char *s);

#endif