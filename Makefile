# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 05:12:18 by mkulbak           #+#    #+#              #
#    Updated: 2025/01/22 14:24:17 by mkulbak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	pipex.c pipex_utils.c split.c libft.c
OBJS			= $(SRCS:.c=.o)


NAME			= pipex
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror


all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus