/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:06:04 by uhand             #+#    #+#             */
/*   Updated: 2019/09/16 15:44:07 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_WAY_H
# define FIND_WAY_H

# include "lem_in.h"

# define CUR find->crnt_set
# define PRE find->crnt_set->prev

/*
** Way params: way
*/

typedef struct			s_way
{
	int					len_way;
	int					num_way;
	int					status;
	int					last_steps;
	int					steps;
	int					full_steps;
	t_dllist			*rooms;
	struct s_way		*next;
	struct s_way		*prev;
}						t_way;

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

struct					s_find_way
{
	t_way_set			*sets;
	t_way_set			*crnt_set;
	t_way_set			*answer;
	t_way				*ways;
	int					way_nbr;
	t_list_rooms		*start;
	t_list_rooms		*del_room;
	t_list_links		*del_link;
	int					check;
	int					check_2;
	int					min_ways;
	int					cnt_ways;
	int					max_way_len;
};

/*
** count_set_steps: c
*/

typedef struct			s_count_steps
{
	t_way				*ptr;
	int					i;
	int					pre_lems;
	int					max_len;
	float				steps;
}						t_count_steps;

/*
** link_breaker: br
*/

typedef struct			s_link_breaker
{
	int					room_nbr;
	t_way				*way;
	t_dllist			*wroom;
	t_list_rooms		**croom;
	t_list_links		*link;
	t_list_rooms		**prev_room;
	t_list				*link_ptr;
}						t_link_breaker;

/*
** wide_breaker: wr
*/

typedef struct			s_wide_breaker
{
	t_list_rooms		*prev_room;
	t_list				*link_ptr;
	t_list_links		*prev_link;
}						t_wide_breaker;

typedef struct			s_search
{
	t_list_rooms		*rooms;
	int					step_nbr;
	int					way_nbr;
	int					cnt;
	struct s_search		*next;
	struct s_search		*prev;

}						t_search;

/*
** form_the_set: fs
*/

typedef struct			s_form_set
{
	t_way				*ptr;
	int					counter;
	int					i;
	int					steps_count;
	int					min_steps_count;
	int					i_min;
}						t_form_set;

typedef struct			s_ants
{
	int					status;
	int 				color;
	int 				finished;
	t_way				*way;
	t_dllist			*rooms;
	t_list_rooms		*position;
}						t_ants;

typedef struct			s_ant_farm
{
	t_ants				*ants;
	int					num;
	int					fin_ants;
	int					full_steps;
	int					ant_flow;
	int					switcher;
	int					i;
	int					j;
}						t_ant_farm;

int						find_the_way(t_intldta *indta);
void					fill_searched(t_search **searched, t_search **search);
int						rec_finding(t_intldta *indta, t_find_way *fnd_wy);
int						wide_search(t_find_way **fnd_wy, t_intldta **indta);
int						link_breaker(t_find_way **find);
void					wide_breaker(t_list_links *link, t_list_rooms *room);
void					dead_end_cleaner(t_list_rooms *room, int prm);
void					print_the_way(t_way *way);
void					print_the_set(t_way_set *set);
void					fill_the_way(t_way **tmp_way, t_search *list);
void					free_search_ed(t_search **search, t_search **searched);
int						not_in_searched(t_list_rooms *rm, t_search *searched,
		t_search *search);
int						fill_search(t_find_way **find, t_search **search,
		t_search **searched, t_intldta **indta);
void					del_t_list_room(t_search **room);
int						it_has_link(t_list_rooms *room1, t_list_rooms *room2);
void					make_it_clean(t_search **lst_rooms);
int						rev_wide_search(t_intldta **indta);
int						pre_link_breaker(t_find_way **fnd, t_list_rooms *room);
int						give_me_way_nbr(t_way **ways);
void					erase_tmp_step_nbr(t_list_rooms *rooms);
void					move_ants(t_intldta *intdta, t_find_way *find);
void					insert_way(t_find_way *find, t_way *way);
void					add_the_way(t_find_way **fnd, t_search **srch,
		t_search **srchd, t_list_links *end_lnk);
void					rev_fill_searched(t_search **searched, t_search
**search);
void					free_indta(t_intldta **intldta);
void					free_main_structs(t_intldta **intldta, t_find_way
**find);
void					free_t_list_links(t_list_links **links);
void					find_cur_room(t_link_breaker *br, t_find_way **find,
		t_list_rooms *room);
void					break_links(t_link_breaker *br);
void					cpy_the_state(t_intldta **inda, t_list_links **lnks,
		t_list_rooms **rms);
void					cpy_the_rooms(t_list_rooms *s_rms,
		t_list_rooms **d_rms);
void					cpy_the_links(t_list_links *s_lnks,
		t_list_links **d_lnks, t_list_rooms *rms);

#endif
