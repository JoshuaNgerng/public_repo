# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 20:22:46 by jngerng           #+#    #+#              #
#    Updated: 2023/07/24 20:22:46 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
SRCS = get_next_line.c get_next_line_utils.c
N_SRCS = ft_strjoin.c ft_calloc.c ft_bzero.c
L_SRCS = $(addprefix ../lib/src/, $(N_SRCS))
L_OBJS = $(L_SRCS:.c=.o)
OBJS = $(SRCS:.c=.o)
INC = -I ../lib/includes
CFLAGS = -Wall -Wextra -Werror
CC = gcc

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INC}

${NAME}: ${OBJS}
	$(MAKE) -C ../lib
	ar rc ${NAME} ${OBJS} ${L_OBJS}

all: ${NAME}

clean:
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C ../lib
	rm -f $(NAME)

re: fclean all
