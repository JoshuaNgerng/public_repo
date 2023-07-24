# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 22:56:37 by jngerng           #+#    #+#              #
#    Updated: 2023/05/30 22:56:37 by jngerng          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BNAME = checker
FIL = main stack utlis sort_arr sort_arr2 op op2 sort_lst sort_lst2
BFIL = main op op2 sort stack utlis
SRC = $(foreach file, $(FIL), src/$(file).c)
BSRC = $(foreach file, $(BFIL), bonus/$(file).c)
OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
INC = -I includes -I ../lib/includes -I ../gnl -I ../printf/includes
LIBFT = -L ../lib -lft -L ../printf -lftprintf -L ../gnl -lgnl
CFLAGS = -Wall -Wextra -Werror
CC = gcc

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o} $(INC)

$(NAME): $(OBJ)
	$(MAKE) -C ../lib
	$(MAKE) -C ../printf
	$(MAKE) -C ../gnl
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INC) $(LIBFT)

all: $(NAME)

bonus: $(BOBJ)
	$(MAKE) -C ../lib
	$(MAKE) -C ../printf
	$(MAKE) -C ../gnl
	$(CC) $(CFLAGS) -o $(BNAME) $(BOBJ) $(INC) $(LIBFT)

oclean:
	rm -f $(OBJ)
	rm -f $(BOBJ)

clean: oclean
	$(MAKE) fclean -C ../lib
	$(MAKE) fclean -C ../printf
	$(MAKE) fclean -C ../gnl

fclean: clean
	rm -f $(NAME)
	rm -f $(BNAME)

re: fclean bonus all