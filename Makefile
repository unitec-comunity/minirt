NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INC = -Iincludes -Idepemdences/minilibx-linux -Idepemdences/next_line

MLX = depemdences/minilibx-linux/libmlx.a -lX11 -lXext

SRC = src/main.c src/init.c src/mlx/mlx_init.c src/mlx/hooks.c \
    src/mlx/image_init.c src/mlx/image_pixel_put.c src/utils/colors.c\
	src/math/vector.c src/math/vect_add.c src/math/vect_sub.c\
	src/math/vect_scale.c src/math/vect_dot.c src/math/vect_length.c\
	src/math/vect_normalize.c src/ray/ray_create.c src/camera/camera.c\
	src/intersecption/intersecption.c src/render/render_scene.c\
	src/math/ray_at.c src/light/light.c  src/shadow.c\
	src/intersecption/find_closest_hit.c src/intersecption/intersect_object.c\
	src/intersecption/intersect_plane.c src/intersecption/intersect_cylinder.c\
	src/intersecption/cylinder_normal.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(MLX) -lm -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re