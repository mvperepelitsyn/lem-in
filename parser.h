/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:45:32 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/17 16:11:15 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NAME "wrong_way_set.txt" //DO NOT FORGET TO REMOVE IT

# include "lem_in.h"

/*
** This is the structure for our room, where:
** name - name of a room;
** type - the parameter that tells to us what room is this, such as:
** 1 - start node;
** 2 - end node;
** 0 - ordinary node;
** links - an adress to the list of links
*/

struct					s_list_rooms
{
	char				*name;
	int					x_cord;
	int					y_cord;
	short				type;
	int					status;
	int					num_lnks;
	int					act_lnks;
	int					step_nbr;
	int					tmp_step_nbr;
	int					way_nbr;
	t_list				*links;
	struct s_list_rooms *prev;
	struct s_list_rooms	*next;
};

struct					s_list_links
{
	char				*room1;
	char				*room2;
	t_list_rooms		*rm1;
	t_list_rooms		*rm2;
	int					sttus;
	int					way_nbr;
	struct s_list_links *next;
};

struct					s_intldta
{
	int					num_ants;
	t_list_rooms		*rooms;
	t_list_links		*links;
	t_list_rooms		*start_room;
	t_list_rooms		*end_room;
	int					ri;
	int					li;
	int					v_flag;
	int					counter;
};

void					ft_malloc_error(void);
void					init_struct(t_intldta **indta);
void					ft_error(void);
void					ft_println(char *str);
void					test_name(const char *name);
int						test_links(t_list_links **links, t_intldta **indta);
void					test_double_room(const char *rm, t_intldta **indta);
int						check_double_link(t_list_links *links, char **rms);
void					graph_parser(t_intldta **indta, char **things,
		char **rms, int fd);
int						fill_list_links(t_list_links **links, char **rms,
		t_intldta **indta);
void					fill_list_rooms(char **rms, t_intldta **indta,
		short type);
void					help_fill_list_rooms(char **rms, t_list_rooms **current,
		short type);
void					free_2d_array(char **array);

#endif
