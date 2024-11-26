NAME = miniRT
LIBFT = ./incl/libft/libft.a
GNL = ./incl/get_next_line/gnl.a
MLX = ./incl/mlx/libmlx.a
INC = -I ./incl
OBJ_DIR = obj/
CC = cc
CFLAGS = -O3 -g $(INC) -Wall -Wextra -Werror 
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
      srcs/intersect.c \
      srcs/matrix_ops.c \
      srcs/movement.c \
      srcs/movement_utils.c \
      srcs/object_selection.c \
      srcs/random_gen.c \
      srcs/render.c \
      srcs/utils_color.c \
      srcs/utils_vec.c \
      srcs/utils.c \
      srcs/main.c \

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

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

clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -C ./incl/libft
	@make clean -C ./incl/get_next_line

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@$(RM) $(GNL)

re: fclean all

.PHONY: start all clean fclean re
