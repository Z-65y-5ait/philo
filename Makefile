CC = cc
NAME = philo
FLAGS = -Wall -Wextra -Werror
SRC = philo.c philo_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re