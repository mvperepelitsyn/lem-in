# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 15:32:06 by uhand             #+#    #+#              #
#    Updated: 2019/09/16 18:51:46 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

HEAD = ./
SRC = helper.c parser.c find_the_ways.c parser_2.c visualizer.c visualizer_2.c \
visualizer_3.c visualiser_4.c rec_finding.c link_breaker.c draw_circle.c \
vis_build_route.c helper_ways.c make_clean_list.c wide_search.c \
wide_search_2.c wide_search_3.c reverse_wide_search.c moving_ants.c parser_3.c \
wide_search_4.c free_structs.c reverse_wide_search_2.c free_structs_2.c \
helper_2.c link_breaker_2.c wide_breaker.c steps_vis.c cpy_the_state.c \
cpy_the_state_2.c

OBJ = $(addprefix $(OBJPATH)/,$(SRC:.c=.o))

FLAGS =  -g #-Wall -Wextra -Werror #-m64 -Ofast -flto -march=native -funroll-loops
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
