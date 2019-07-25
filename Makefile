# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/02 12:28:41 by iiliuk            #+#    #+#              #
#    Updated: 2019/07/25 16:54:12 by dfrost-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in

CC      =  gcc -Wall -Wextra -Werror

SRC 	= checker.c helper.c helper_to_a.c helper_to_b.c parser.c

INCLUDES = libft/includes

OBJ 	= $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft/ re
	@$(CC) -I $(INCLUDES) -c $(SRC)
	@$(CC) -o $(NAME) $(OBJ) -I $(INCLUDES) -L libft/ -lft

clean:
	@/bin/rm -f $(OBJ)
	@make -C ./libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all
