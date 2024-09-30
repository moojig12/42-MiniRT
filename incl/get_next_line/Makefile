# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 15:02:29 by nmandakh          #+#    #+#              #
#    Updated: 2024/09/30 08:43:38 by nmandakh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			= get_next_line.c get_next_line_utils.c

OBJS			= $(SRCS:.c=.o)

OBJS_B			= $(SRCS_B:.c=.o)

OBJS_ALL		= $(OBJS) $(OBJS_B)

CC				= cc
RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= gnl.a

all:		$(NAME)

$(NAME):	$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(OBJS_B)
fclean:		clean
				$(RM) $(NAME)
re:				fclean $(NAME)

.PHONY:			all clean fclean re