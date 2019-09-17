/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:20:44 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/17 12:11:57 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_the_way(t_way *way)
{
	t_way			*tmp;
	t_dllist		*ptr;
	t_list_rooms	**ptr2;
	t_list_rooms	*ptr3;

	tmp = way;
	ptr = tmp->rooms;
	ft_putstr("\n");
	while (ptr != NULL)
	{
		ptr2 = ptr->content;
		ptr3 = (*ptr2);
		if (ptr->right != NULL)
			ft_printf("%s->", ptr3->name);
		else
			ft_printf("%s", ptr3->name);
		ptr = ptr->right;
	}
	ft_printf("\t:%d", (*way).len_way);
	if ((*way).len_way == 60)
		(*way).len_way = 60;
	ft_putstr("\n");
}

static void		init_set(t_find_way **fnd_wy, t_intldta *indta)
{
	if (!((*fnd_wy) = (t_find_way *)ft_memalloc(sizeof(t_find_way))))
		ft_malloc_error();
	(*fnd_wy)->ways = NULL;
	(*fnd_wy)->start = indta->start_room;
	(*fnd_wy)->sets = NULL;
	(*fnd_wy)->crnt_set = NULL;
	(*fnd_wy)->way_nbr = 0;
	(*fnd_wy)->del_room = NULL;
	(*fnd_wy)->check = 1;
}

static void		set_pre_lems(t_find_way *find)
{
	t_list			*ptr;
	t_way			**way_ptr;

	ptr = find->answer->ways;
	find->max_way_len = 0;
	while (ptr)
	{
		way_ptr = ptr->content;
		if (find->max_way_len < way_ptr[0]->len_way)
			find->max_way_len = way_ptr[0]->len_way;
		ptr = ptr->next;
	}
	ptr = find->answer->ways;
	while (ptr)
	{
		way_ptr = ptr->content;
		way_ptr[0]->last_steps = find->max_way_len - (way_ptr[0]->len_way - 1);
		ptr = ptr->next;
	}
}

static void		help_find_the_way(t_intldta **indta, t_find_way **find)
{
	rev_wide_search(indta);
	(*indta)->start_room->tmp_step_nbr = 0;
	if ((*indta)->start_room->act_lnks == 0)
		ft_error();
	init_set(find, *indta);
	while (!rec_finding(*indta, *find))
		continue ;
	(*find)->answer = (*find)->sets;
}

int				find_the_way(t_intldta *indta)
{
	t_find_way	*find;
	int			steps;
	t_way_set	*ptr;
	t_list_links *t_lnks;
	t_list_rooms *t_rms;

	help_find_the_way(&indta, &find);
	ptr = find->answer;
	steps = ptr->steps;
	while (ptr)
	{
		if (ptr->steps < steps)
		{
			find->answer = ptr;
			steps = ptr->steps;
		}
		ptr = ptr->next;
	}
	set_pre_lems(find);
	move_ants(indta, find);
	if (indta->v_flag)
		visualizer(indta, find);
	cpy_the_state(&indta, &t_lnks, &t_rms);
	free_main_structs(&indta, &find);
	return (0);
}
