# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/02 12:28:41 by iiliuk            #+#    #+#              #
#    Updated: 2019/07/02 14:44:17 by dfrost-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1	= checker

NAME2   = push_swap

CC      =  gcc -Wall -Wextra -Werror

SRC1 	= checker.c apply_cmd_ch.c apply_cmd_ch_1.c apply_cmd_ch_2.c\
helper.c helper_to_a.c helper_to_b.c parser.c

SRC2   = push_swap.c sort.c helper.c parser.c apply_cmd_ps.c apply_cmd_ch.c\
apply_cmd_ch_1.c apply_cmd_ch_2.c apply_cmd_ps_1.c apply_cmd_ps_2.c\
sort_helper.c helper_to_a.c helper_to_b.c new_sort.c utils_sort.c

INCLUDES = libft/includes

OBJ1 	= $(SRC1:.c=.o)

OBJ2    = $(SRC2:.c=.o)

all: $(NAME1) $(NAME2)

$(NAME1):
	@make -C libft/ re
	@$(CC) -I $(INCLUDES) -c $(SRC1)
	@$(CC) -o $(NAME1) $(OBJ1) -I $(INCLUDES) -L libft/ -lft

$(NAME2):
	@make -C libft/ re
	@$(CC) -I $(INCLUDES) -c $(SRC2)
	@$(CC) -o $(NAME2) $(OBJ2) -I $(INCLUDES) -L libft/ -lft

clean:
	@/bin/rm -f $(OBJ1)
	@/bin/rm -f $(OBJ2)
	@make -C ./libft/ clean

fclean: clean
	@/bin/rm -f $(NAME1)
	@/bin/rm -f $(NAME2)
	@make -C ./libft/ fclean

re: fclean all
