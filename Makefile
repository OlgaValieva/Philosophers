# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carys <carys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 14:41:05 by carys             #+#    #+#              #
#    Updated: 2022/05/26 13:40:46 by carys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

HEADER	=	philo.h

SRCS	=	ft_philo.c  ft_init.c  ft_life.c  ft_utils.c

OBJS	=	${SRCS:%.c=%.o}

CC		=	cc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -I{HEADER}

.PHONY:		all clean fclean re

all: ${NAME}

%.o:	%.c ${HEADER}
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
