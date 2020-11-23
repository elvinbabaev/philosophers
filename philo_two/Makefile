NAME = philo_two

INC = philo_two.h

SRC = error.c philo_init.c philo_two.c \
		utils/utils.c thread.c dinner.c write_msg.c time.c

all: $(NAME)

$(NAME):$(SRC) $(INC)
	gcc $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all
