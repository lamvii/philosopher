# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-idri <ael-idri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 18:48:39 by ael-idri          #+#    #+#              #
#    Updated: 2022/07/06 19:43:14 by ael-idri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 	=	philo_bonnus
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
SRCS	 	=	philo_bonnus.c utils_bonnus.c init_bonnus.c 			\
				check_arg_bonnus.c		
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