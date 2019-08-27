/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:06:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/27 18:08:54 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_WAY_H
# define FIND_WAY_H

#include "lem_in.h"

# define CUR find->crnt_set
# define PRE find->crnt_set->prev

/*
** Way params: way
*/

typedef struct		s_way
{
	int				len_way;
	int				num_way;
	int				status;
	t_dllist		*rooms;
	struct  s_way	*next;
	struct	s_way	*prev;
}					t_way;

/*
** Way set params: set
*/

typedef struct			s_way_set
{
	int					steps;
	int					full_steps;
	int					ways_cnt;
	t_list				*ways;
	struct s_way_set	*next;
	struct s_way_set	*prev;
}						t_way_set;

/*
**  find_the_way params: find
*/

struct	s_find_way
{
	t_way_set		*sets;  // сurrent set
	t_way_set		*crnt_set;  // сurrent set
	t_way_set		*answer;
	t_way			*ways;
	int 			way_nbr;
	t_list_rooms	*start;
};

/*
** count_set_steps: c
*/

typedef struct	s_count_steps
{
	t_list			*ptr;
	t_way			*way;
	int				pre_lems;
	int				max_len;
	float			steps;
	//int			len;
}				t_count_steps;

/*
** link_breaker: br
*/

typedef struct	s_link_breaker
{
	t_way			*way;
	t_dllist		*wroom;
	t_list_rooms	*croom;
	t_list_links	*link;
	t_list_rooms	*prev_room;
	t_list			*link_ptr;
}				t_link_breaker;

int 	find_the_way(t_intldta *indta);
void	cpy_t_list_room(t_list_rooms *dest, t_list_rooms *src, int way_nbr);
void	fill_searched(t_list_rooms **searched, t_list_rooms **search, int way_nbr);
int		rec_finding(t_intldta *indta, t_find_way *fnd_wy);
int		wide_search(t_find_way **fnd_wy, t_intldta **indta);
int		link_breaker(t_find_way *find, t_list_rooms *room);

#endif
