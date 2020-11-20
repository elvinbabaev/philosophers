NAME = philo_three

INC = philo_three.h

SRC = error.c philo_init.c philo_three.c \
		utils/utils.c fork_phil.c dinner.c write_msg.c

all: $(NAME)

$(NAME):$(SRC) $(INC)
	gcc $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all
