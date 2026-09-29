NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -std=gnu17

INC = -Iincludes -Idepemdences/minilibx-linux -Idepemdences/next_line

MLX_DIR = depemdences/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_CC = $(CC)
MLX_INC = $(shell sed -n 's/^INC=//p' $(MLX_DIR)/Makefile.gen)
MLX = $(MLX_LIB) -lX11 -lXext

SRC = src/main.c src/init.c src/parse/scene_validate.c \
	src/parse/scene_parse_values.c src/parse/scene_parse_range.c \
	src/parse/scene_parse_record.c src/parse/scene_parse_line.c \
	src/mlx/mlx_init.c src/mlx/hooks.c \
	src/mlx/image_init.c src/mlx/image_pixel_put.c src/utils/colors.c \
	src/math/vector.c src/math/vect_add.c src/math/vect_sub.c \
	src/math/vect_scale.c src/math/vect_dot.c src/math/vect_length.c \
	src/math/vect_normalize.c src/ray/ray_create.c src/camera/camera.c \
	src/intersecption/intersecption.c src/render/render_scene.c \
	src/math/ray_at.c src/light/light.c src/shadow.c \
	src/intersecption/find_closest_hit.c src/intersecption/intersect_object.c \
	src/intersecption/intersect_plane.c src/intersecption/intersect_cylinder.c \
	src/intersecption/cylinder_normal.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(MLX) -lm -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) -f Makefile.gen CC=$(MLX_CC) \
		CFLAGS="-O3 -I$(MLX_INC) -std=gnu17"

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ) depemdences/next_line/get_next_line.o \
		depemdences/next_line/get_next_line_utils.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
