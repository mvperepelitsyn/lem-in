/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:35:18 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/28 13:57:31 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# define NAME "../test.lemin" //DO NOT FORGET TO REMOVE IT

# include "libft/includes/libft.h"

typedef struct			s_room
{
	char				*name;
	long int			x_cord;
	long int			y_cord;
}						t_room;

typedef struct			s_list_rooms
{
	t_room				*room;
	int 				i;
	struct s_list_rooms	*next;
}						t_list_rooms;

typedef struct			s_list_links
{
	char				*room1;
	char 				*room2;
	int 				i;
	struct				s_list_links *next;
}						t_list_links;

typedef struct		s_test
{
	long int		num_ants;
	t_list_rooms	*rooms;
	t_list_links	*links;
	t_room			*start_room;
	t_room			*end_room;
}					t_test;

void	ft_malloc_error(void);
void	ft_print_strcut(t_test **test);
void	init_struct(t_test **test);
void 	ft_error(void);
void	ft_println(char *str);
void	test_coord(long int x, long int y);
void	test_name(const char *name);
int 	test_links(const char *rm1, const char *rm2, t_test *test);
void	test_double_room(const char *rm, t_test **test);


void	free_2d_array(char **array);

#endif
