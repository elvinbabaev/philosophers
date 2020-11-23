NAME = philo_three

INC = philo_three.h

SRC = error.c philo_init.c philo_three.c \
		utils/utils.c fork_phil.c dinner.c write_msg.c

FLAGS = -Wall -Wextra -Werror

OSRC = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OSRC) $(INC)
	gcc $(OSRC) -o $(NAME)

%.o: %.c $(HEADER)$(INC)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OSRC)

fclean:clean
	rm -rf $(NAME)

re: fclean all

.PHONE: all clean fclean re
