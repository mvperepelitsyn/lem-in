/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:35:18 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/08/01 18:33:52 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# define NAME "../test.lemin" //DO NOT FORGET TO REMOVE IT

# include "libft/libft.h"

/*
 * This is the structure for our graph, where:
 * name - name of a node
 * type - the parameter tells to us what room is this, such as:
 * 1 - start node;
 * 2 - end node;
 * 0 - ordinary node;
 * lnod - a list which contains all nodes linked to the node
 *
 */

typedef struct			s_room
{
	char				*name;
	long int			x_cord;
	long int			y_cord;
	short				type;
	int 				num_lnks;
	t_list				*links;

}						t_room;

typedef struct			s_list_rooms
{
	t_room				*room;
	int 				i;
	struct s_list_rooms	*next;
}						t_list_rooms;

//TODO: Change i for t_list_links and move it to the core structure

typedef struct			s_list_links
{
	char				*room1;
	char 				*room2;
	t_room				*rm1;
	t_room				*rm2;
	short 				dir;
	int 				i;
	struct s_list_links *next;
}						t_list_links;

//TODO: add start and end rooms to all rooms

typedef struct		s_intldta
{
	long int		num_ants;
	t_list_rooms	*rooms;
  	t_list_links	*links;
	t_room			*start_room;
	t_room			*end_room;
}					t_intldta;  //initial data

void	ft_malloc_error(void);
void	ft_print_strcut(t_intldta **indta);
void	init_struct(t_intldta **indta);
void 	ft_error(void);
void	ft_println(char *str);
void	test_coord(long int x, long int y);
void	test_name(const char *name);
int 	test_links(const char *rm1, const char *rm2, t_intldta *indta);
void	test_double_room(const char *rm, t_intldta **indta);
int 	check_double_link(t_list_links *links, char **rms);
void    graph_parser(t_intldta **indta, char *things, char **rms, int fd);
void	fill_list_links(t_list_links **links, char **rms, t_intldta *indta);
void	fill_list_rooms(char **rms, t_intldta **indta);

void	help_fill_list_rooms(char **rms, t_room **current);


void	free_2d_array(char **array);

#endif
