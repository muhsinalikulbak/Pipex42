# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 05:12:18 by mkulbak           #+#    #+#              #
#    Updated: 2025/02/05 04:41:41 by mkulbak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	pipex.c pipex_utils.c split.c libft.c
SRCS_B			= 	pipex_bonus.c pipex_utils_bonus.c libft.c split.c

OBJS			= $(SRCS:.c=.o)
OBJS_B			= $(SRCS_B:.c=.o)

NAME			= pipex
NAME_B			= pipex_bonus

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g


all:			$(NAME)

bonus:			$(NAME_B)

$(NAME_B):		$(OBJS_B)
				$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS) $(OBJS_B)

fclean:			clean
				$(RM) $(NAME) $(NAME_B)

re_bonus:		fclean bonus

re:				fclean all

.PHONY:			all clean fclean re bonus re_bonus bonus	