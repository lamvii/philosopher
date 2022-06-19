# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 00:11:33 by ael-idri          #+#    #+#              #
#    Updated: 2022/06/19 01:02:38 by ael-idri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 	=	philo
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
SRCS	 	=	philosopher.c utils.c initialise_philos.c check_arg.c
OBJS		=	$(SRCS:.c=.o)
HEADER		=	philosopher.h


all			:	$(NAME)

$(NAME)		:	$(OBJS) 
				${CC} ${FLAGS} ${OBJS} -o $(NAME)

%.o			:	%.c $(HEADER)
				$(CC) ${FLAGS} -c $< -o $@
    
clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re