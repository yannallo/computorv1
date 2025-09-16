NAME = computorv1
CC = gcc
FLAG = -Wall -Wextra -Werror
LEAK = -fsanitize=leak $(FLAG)
SRC = main.c parse.c solve.c refacto.c term.c utils.c ft_split.c
OBJ = $(SRC:.c=.o)
INCLUDE = -lm

all: $(NAME)

leak: $(OBJ)
	$(CC) $(LEAK) $(INCLUDE) -o $(NAME) $(OBJ)

$(NAME): $(OBJ)
	$(CC) $(INCLUDE) -o $(NAME) $(OBJ)

%.o: %.c Makefile
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
