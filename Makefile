NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INC = -Iincludes -Idepemdences/minilibx-linux -Idepemdences/next_line

MLX = depemdences/minilibx-linux/libmlx.a -lX11 -lXext

SRC = src/main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
