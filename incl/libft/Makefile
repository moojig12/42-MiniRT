# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmandakh <nmandakh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 15:38:14 by nmandakh          #+#    #+#              #
#    Updated: 2023/11/21 18:12:24 by nmandakh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# SRCS			=	./*.c

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c \
					ft_strlcat.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
					ft_memcpy.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
					ft_memmove.c ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c  ft_memset.c \
					ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
					ft_itoa.c ft_strmapi.c ft_striteri.c ft_putendl_fd.c \
					ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
					

SRCS_B			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
					ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
					ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS			= $(SRCS:.c=.o)

OBJS_B			= $(SRCS_B:.c=.o)

OBJS_ALL		= $(OBJS) $(OBJS_B)

CC				= cc
RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
				ar rcs $(NAME) $(OBJS)

bonus:		$(OBJS_B) $(NAME)
				ar rcs $(NAME) $(OBJS_B)
clean:
				$(RM) $(OBJS) $(OBJS_B)
fclean:		clean
				$(RM) $(NAME)
re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus

everything: $(OBJS_ALL)
	$(CC) $(CCFLAGS) $? -o $(NAME)