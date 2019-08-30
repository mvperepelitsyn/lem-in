# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iiliuk <iiliuk@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/02 12:28:41 by iiliuk            #+#    #+#              #
#    Updated: 2019/08/30 14:05:18 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

HEAD = ./
SRC = helper.c parser.c find_the_ways.c parser_2.c visualizer.c visualizer_2.c \
visualizer_3.c visualiser_4.c rec_finding.c link_breaker.c

OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))

FLAGS = -g #-Wall -Wextra -Werror
LIB = -L ./libft -lft
LIBPATH = ./libft

MLIBX = -L  ./minilibx -lmlx -framework OpenGL -framework AppKit
MLIBXPATH = ./minilibx
OBJPATH = ./objects

all: $(NAME)

$(NAME):  $(OBJPATH) $(OBJ)
	@make -C $(LIBPATH)
	@make -C $(MLIBXPATH)
	gcc $(FLAGS) $(OBJ) -o $(NAME) $(LIB) $(MLIBX)

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(OBJPATH)/%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBPATH) clean
	@make -C $(MLIBXPATH) clean
	/bin/rm -rf $(OBJPATH)

fclean: clean
	@make -C $(LIBPATH) fclean
	@make -C $(MLIBXPATH) fclean
	/bin/rm -f $(NAME)

re: fclean all
