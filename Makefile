NAME = miniRT
NAME_THREAD = miniRT_threaded
LIBFT = ./incl/libft/libft.a
GNL = ./incl/get_next_line/gnl.a
MLX_DIR = ./incl/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_LIB_LINK = https://github.com/42Paris/minilibx-linux.git
INC = -I ./incl -I $(MLX_DIR)
OBJ_DIR = obj/
OBJ_B_DIR = obj_thread/
CC = cc
CFLAGS = -O3 -pthread -g $(INC) -Wall -Wextra -Werror
MFLAG = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
RM = rm -f

# Tools
GIT = /usr/bin/git
MAKE_TOOL = /usr/bin/make

# Source files
SRC = srcs/parser/checks.c \
      srcs/parser/parse_amb.c \
      srcs/parser/parse_cam.c \
      srcs/parser/parse_cyl.c \
      srcs/parser/parse_lig.c \
      srcs/parser/parse_obj.c \
      srcs/parser/parse_plane.c \
      srcs/parser/parse_sphere.c \
      srcs/parser/parse_utils.c \
      srcs/parser/parse_utils2.c \
      srcs/parser/utils_p.c \
      srcs/parser/parse.c \
      srcs/cam_ray.c \
      srcs/error.c \
      srcs/free.c \
      srcs/free2.c \
      srcs/intersect.c \
      srcs/intersect_helper.c \
      srcs/intersect_helper2.c \
      srcs/matrix_ops.c \
      srcs/matrix_ops2.c \
      srcs/movement.c \
      srcs/movement_utils.c \
      srcs/object_selection.c \
      srcs/random_gen.c \
      srcs/render.c \
      srcs/utils_color.c \
      srcs/utils_color2.c \
      srcs/utils_vec.c \
      srcs/utils.c \
      srcs/utils_print.c \
      srcs/utils_selection.c \
      srcs/utils_vec2.c \
      srcs/utils_atof.c \
      srcs/movement_misc.c \
      srcs/render_modes.c \
      srcs/utils_render.c \
      srcs/utils_material.c \
      srcs/main.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

HEADERS = incl/minirt.h

start:
	@make all

all: mlx $(LIBFT) $(GNL) $(NAME)

# MLX Installation and Build
mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MinilibX repository..."; \
		$(GIT) clone $(MLX_LIB_LINK) $(MLX_DIR); \
	else \
		echo "MinilibX already exists, skipping clone."; \
	fi
	@echo "Building MinilibX library..."
	@$(MAKE_TOOL) -C $(MLX_DIR)
	@echo "MinilibX build complete!"

# Building libft and get_next_line
$(LIBFT):
	@make -C ./incl/libft

$(GNL):
	@make -C ./incl/get_next_line

$(NAME): $(OBJ) $(LIBFT) $(GNL) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) -o $(NAME) $(MFLAG)

$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./incl/libft
	@make clean -C ./incl/get_next_line
	@make clean -C $(MLX_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(GNL)
	@make clean -C $(MLX_DIR)

re: fclean all

.PHONY: start all mlx clean fclean re
