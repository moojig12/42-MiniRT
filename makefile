NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I./incl
MFLAGS		= -Lincl/mlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
LIBS		= ./incl/libft/libft.a ./incl/mlx/libmlx.a

SRCS		= main.c

SRCS_P		= srcs

OBJS		= $(SRCS_P)/$(SRCS:.c=.o)

OBJS_P	= objs


all:	$(NAME)

$(OBJS_P)/%.o: $(SRC_P)/%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
			make -C ./incl/mlx
			make -C ./incl/libft
			$(CC) $(CFLAGS) $(LIBS) $(LFLAGS) $(OBJS) -o $(NAME) $(MFLAGS)


clean:
			# make clean -C ./incl/mlx
			make clean -C ./incl/libft
			rm -f $(OBJS)

fclean:	clean
			# make fclean -C ./incl/mlx
			make fclean -C ./incl/libft
			rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re