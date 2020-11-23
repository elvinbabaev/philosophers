NAME = philo_two

INC = philo_two.h

SRC = error.c philo_init.c philo_two.c \
		utils/utils.c thread.c dinner.c write_msg.c time.c

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
