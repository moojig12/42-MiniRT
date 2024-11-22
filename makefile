NAME	=	miniRT

CC		=	cc
HEADER	=	-I./incl -I./incl/mlx -I./incl/libft -I./incl/get_next_line
SAN		=	-fsanitize=address
CFLAGS	=	-O3 -Ilibmlx -g $(HEADER)
MFLAGS  =	-L /usr/X11R6/lib -lXext -lX11 -lm

LIBS	=	./incl/libft/libft.a ./incl/mlx/libmlx.a ./incl/get_next_line/gnl.a


SRCS	=	main.c \
			parser/parse.c \
			parser/parse_amb.c \
			parser/parse_obj.c \
			parser/parse_utils.c \
			parser/parse_cam.c \
			parser/parse_cyl.c \
			parser/parse_lig.c \
			parser/parse_plane.c \
			parser/parse_sphere.c \
			parser/checks.c \
			parser/utils_p.c \
			error.c \
			free.c \
			random_gen.c \
			render.c \
			movement.c \
			matrix_ops.c \
			intersect.c \
			utils.c \
			utils_color.c \
			utils_vec.c

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
			make -C ./incl/get_next_line
			make -C ./incl/libft
			make -C ./incl/mlx
			$(CC) $(HEADER) $(SAN) $(CFLAGS) $(OBJS) $(LIBS) \
			-o $(NAME) $(MFLAGS)

no_san:	CFLAGS := $(filter-out $(SAN), $(CFLAGS))
no_san: $(OBJS)
			make -C ./incl/get_next_line
			make -C ./incl/libft
			make -C ./incl/mlx
			$(CC) $(HEADER) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(MFLAGS)

clean:
			make clean -C ./incl/libft
			make clean -C ./incl/get_next_line
			# make clean -C ./mlx
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)
			rm -rf $(LIBS)

re:			fclean all

.PHONY: all clean fclean re