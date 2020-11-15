NAME = philo_one

INC = philo_one.h

SRC = error.c philo_init.c philo_one.c \
		utils/utils.c thread.c dinner.c write_msg.c

all: $(NAME)

$(NAME):$(SRC) $(INC)
	gcc $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all
