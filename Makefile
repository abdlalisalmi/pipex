# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/22 19:41:05 by aes-salm          #+#    #+#              #
#    Updated: 2021/06/22 21:38:32 by aes-salm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex.a
CC 		= gcc
FLAGS	= -Wall -Werror -Wextra
SRCS	= 	functions/ft_split.c \
			functions/ft_strlen.c \




$(NAME) : 	$(SRCS)
			@ $(CC) $(FLAGS) -c $(SRCS)
			@ ar rc $(NAME) *.o
			@ $(CC) $(FLAGS) main.c $(NAME) -o pipex

all:		$(NAME)

clean:		
			@ rm -rf *.o

fclean:		clean
			@ rm -rf $(NAME) pipex pipex.dSYM

re:			fclean all

test: 	re
		@ rm -rf $(NAME) pipex.dSYM *.o