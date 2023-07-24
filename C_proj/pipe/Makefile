# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 19:12:39 by jngerng           #+#    #+#              #
#    Updated: 2023/05/08 19:12:39 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
S_NAME = main get_cmd pro_cmd sp utlis free_ex
SRC = $(foreach file, $(S_NAME), src/$(file).c)
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I includes -I ../lib/includes -I ../gnl -I ../printf/includes

LIBFT = -L ../lib -lft
PRINTF = -L ../printf -lftprintf
GNL = -L ../gnl -lgnl

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} $(INC)

$(NAME): $(OBJ)
	$(MAKE) -C ../lib
	$(MAKE) -C ../printf
	$(MAKE) -C ../gnl
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT) $(PRINTF) $(GNL)

all : $(NAME)

oclean:
	rm -f $(OBJ)

clean: oclean
	$(MAKE) clean -C ../lib
	$(MAKE) clean -C ../printf
	$(MAKE) clean -C ../gnl

fclean: clean
	rm -f ../lib/libft.a
	rm -f ../printf/libftprintf.a
	rm -f ../gnl/libgnl.a
	rm -f $(NAME)

re: fclean all
