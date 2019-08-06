# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uhand <uhand@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/18 18:04:25 by uhand             #+#    #+#              #
#    Updated: 2019/08/06 16:39:56 by uhand            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEAD = libft.h get_next_line.h
SRC = ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putendl.c \
ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_strlen.c ft_isalpha.c \
ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strequ.c ft_strnequ.c ft_strstr.c ft_strnstr.c \
ft_strcmp.c ft_strncmp.c ft_atoi.c ft_memalloc.c ft_strnew.c ft_memset.c \
ft_bzero.c ft_strclr.c ft_memchr.c ft_memcmp.c ft_memdel.c ft_strdel.c \
ft_strdup.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_order.c \
ft_itoa.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_memcpy.c \
ft_memccpy.c ft_memmove.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c \
ft_strlcat.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
ft_lstmap.c ft_lstfree.c ft_lstaddnext.c ft_lstdelfirst.c get_next_line.c \
ft_lstcount.c ft_abs.c ft_isspace.c ft_arrjoin.c ft_strsplitspaces.c \
ft_lstcpy.c ft_lstswap.c ft_dllnew.c ft_dlldelone.c ft_dlldeltoright.c \
ft_dlldeltoleft.c ft_dlladdtoleft.c ft_dlladdtoright.c ft_dllrcount.c \
ft_dlllcount.c ft_dllccount.c ft_dllswap.c ft_dlldel.c ft_dlladdnextr.c \
ft_dlladdnextl.c ft_dllcpyr.c ft_dllcpyl.c ft_dllcpy.c ft_nstrjoin.c \
ft_hm_wrd.c ft_latoi.c ft_lstnew_addr.c

SRC_PF = ft_printf.c lib_printf.c add_fnctns.c set_format.c apply_flags.c \
formats_c_s.c format_float.c formats_int.c pft_itoa.c pft_unsigned_itoa.c \
pft_float_itoa.c pft_float_itoa_2.c pft_float_itoa_3.c double_rep.c \
ft_sprintf.c ft_fdprintf.c

SRC_2 = $(addprefix ft_printf/,$(SRC_PF))

OBJ = $(SRC:.c=.o) $(SRC_2:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ): $(SRC) $(HEAD) $(SRC_2)
	@make -C ./ft_printf
	@gcc -c $(SRC) $(FLAGS)

clean:
	@make -C ./ft_printf clean
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
