NAME = computorv1

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinclude

HEADER = include/computorv1.h

SRC = srcs/main.c srcs/token.c srcs/valid.c srcs/parse.c srcs/refacto.c srcs/solve.c srcs/utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re leak
