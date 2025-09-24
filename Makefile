NAME = computorv1

CC = gcc
FLAG = -Wall -Wextra -Werror
LEAK = -fsanitize=address -g
INCLUDE = -lm

HEADER = computorv1.h
SRC = main.c token.c parse.c refacto.c solve.c utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

leak: FLAG += $(LEAK)
leak: INCLUDE += $(LEAK)
leak: re

$(NAME): $(OBJ)
	$(CC) $(INCLUDE) -o $(NAME) $(OBJ)

%.o: %.c Makefile $(HEADER) 
	$(CC) $(FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re leak
