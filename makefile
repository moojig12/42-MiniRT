NAME	=	miniRT

CC		=	cc
HEADER	=	-I./incl -I./incl/mlx -I./incl/libft -I./incl/get_next_line
CFLAGS	=	-fsanitize=address -O2 -Wall -Werror -Wextra -Ilibmlx -g $(HEADER)
MFLAGS  =	-L /usr/X11R6/lib -lXext -lX11 -lm

LIBS	=	./incl/libft/libft.a ./incl/mlx/libmlx.a ./incl/get_next_line/gnl.a


SRCS	=	main.c \
			parser/parse.c \
			parser/parse_amb.c parser/parse_obj.c parser/parse_utils.c \
			parser/checks.c \
			parser/utils_p.c \
			error.c \
			free.c \
			utils.c \

OBJS	=	$(addprefix srcs/, $(SRCS:.c=.o))

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
			make -C ./incl/get_next_line
			make -C ./incl/libft
			make -C ./incl/mlx
			$(CC) $(HEADER) $(CFLAGS) $(OBJS) $(LIBS) \
			-o $(NAME) $(MFLAGS)

clean:
			make clean -C ./incl/libft
			make clean -C ./incl/get_next_line
			# make clean -C ./mlx
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re