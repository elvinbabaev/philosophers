/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:22:35 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 16:22:36 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

# define SEC_MICRO 1000000
# define MIL_SEC_MICRO 1000
# define ERROR 0
# define SUCCESS 1
# define TAB "\t"
# define SIT_DOWN " сел за стол\n"
# define TAKE_FORK " взял вилку"
# define DIED " DIED\n"
# define EAT_UP " поел\n"
# define SLEEP " sleep\n"
# define THINKS " THINKS\n"
# define EAT	" eat_up\n"
# define TAKE_LEFT_FORK " take_left_fork\n"
# define TAKE_RIGHT_FORK " take_right_fork\n"
# define EVERYONE_ATE "everyone ate\n"
# define DROPPED_THE_LEFT_FORK " dropped the left fork\n"
# define DROPPED_THE_RIGHT_FORK " dropped the RIGHT fork\n"
# define ERROR_ARG "wrong number of arguments\n"

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLDBLACK   "\033[1m\033[30m"
# define BOLDRED     "\033[1m\033[31m"
# define BOLDGREEN   "\033[1m\033[32m"
# define BOLDYELLOW  "\033[1m\033[33m"
# define BOLDBLUE    "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN    "\033[1m\033[36m"
# define BOLDWHITE   "\033[1m\033[37m"

typedef enum		e_colour
{
	Reset = 0,
	Green = 1,
	White = 2,
	Magenta = 3,
	Cyan = 4,
	BoldYellow = 5,
	Bolded = 6
}					t_colour;

typedef struct		s_param
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_param;

typedef struct		s_mutex
{
	pthread_mutex_t	*mutex;
}					t_mutex;

typedef struct		s_phil
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
	struct timeval	last_eat;
}					t_phil;

/*
** core function
*/

void				ft_error(char *s);
int					param_init(t_param *param, int ac, char **av);
t_phil				*phil_init(t_param param);
int					create_thread(t_phil *phil, t_param param, int i);
void				*dinner(void *argc);
int					phil_full_msg(int time, int phil, char *msg);
long long int		get_time(struct timeval time_old, struct timeval time_new);
void				my_usleep(size_t time);
void				printer_every_eat(t_phil *phil);
void				printer_phil_died(t_phil *phil, int id_phil);

/*
** utils function
*/

size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);
void				ft_putnbr(int n);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_itoa(int n);
char				*ft_strdup(const char *src);

#endif
