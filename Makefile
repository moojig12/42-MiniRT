NAME = miniRT
NAME_THREAD = miniRT_threaded
LIBFT = ./incl/libft/libft.a
GNL = ./incl/get_next_line/gnl.a
MLX = ./incl/mlx/libmlx.a
INC = -I ./incl
OBJ_DIR = obj/
OBJ_B_DIR = obj_thread/
CC = cc
CFLAGS = -O3 -pthread -g $(INC) -Wall -Wextra -Werror
MFLAG = -L /usr/X11R6/lib -lXext -lX11 -lm
RM = rm -f

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
      srcs/parser/utils_p.c \
      srcs/parser/parse.c \
      srcs/cam_ray.c \
      srcs/error.c \
      srcs/free.c \
      srcs/free2.c \
      srcs/intersect.c \
      srcs/intersect_helper.c \
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

SRC_B = srcs/parser_bonus/checks_bonus.c \
      srcs/parser_bonus/parse_amb_bonus.c \
      srcs/parser_bonus/parse_cam_bonus.c \
      srcs/parser_bonus/parse_cyl_bonus.c \
      srcs/parser_bonus/parse_lig_bonus.c \
      srcs/parser_bonus/parse_obj_bonus.c \
      srcs/parser_bonus/parse_plane_bonus.c \
      srcs/parser_bonus/parse_sphere_bonus.c \
      srcs/parser_bonus/parse_utils_bonus.c \
      srcs/parser_bonus/utils_p_bonus.c \
      srcs/parser_bonus/parse_bonus.c \
      srcs/parser_bonus/parse_emission.c \
      srcs/cam_ray.c \
      srcs/error.c \
      srcs/free.c \
      srcs/free2.c \
      srcs/intersect.c \
      srcs/intersect_helper.c \
      srcs/matrix_ops.c \
      srcs/matrix_ops2.c \
      srcs/movement.c \
      srcs/movement_utils.c \
      srcs/object_selection.c \
      srcs/random_gen.c \
      srcs/utils_color.c \
      srcs/utils_color2.c \
      srcs/utils_vec.c \
      srcs/utils.c \
      srcs/utils_print.c \
      srcs/utils_selection.c \
      srcs/utils_vec2.c \
      srcs/utils_atof.c \
      srcs/movement_misc.c \
      srcs/render_thread.c \
      srcs/render_modes.c \
      srcs/utils_render.c \
      srcs/render_thread_sub.c \
      srcs/utils_material.c \
      srcs/main.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_B = $(addprefix $(OBJ_B_DIR), $(SRC_B:.c=.o))

HEADERS = incl/minirt.h \


start:
	@make all

$(LIBFT):
	@make -C ./incl/libft
$(GNL):
	@make -C ./incl/get_next_line
$(MLX):
	@make -C ./incl/mlx

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(GNL) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) $(MLX) -o $(NAME) $(MFLAG)

$(OBJ_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

thread: $(NAME_THREAD)

$(NAME_THREAD): $(OBJ_B) $(LIBFT) $(GNL) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) $(GNL) $(MLX) -o $(NAME_THREAD) $(MFLAG)

$(OBJ_B_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_B_DIR)
	@make clean -C ./incl/libft
	@make clean -C ./incl/get_next_line

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(GNL)

re: fclean all

.PHONY: start all clean fclean re
