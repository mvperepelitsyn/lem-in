/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_finding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:59:54 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 17:20:23 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_free_rooms(t_list_rooms *start)
{
	t_list			*ptr;
	t_list_links	*link;
	t_list_rooms	*room;

	room = start;
	if (!start->act_lnks)
		return (0);
	ptr = start->links;
	while (ptr)
	{
		link = *(t_list_links **)ptr->content;
		if (!link->sttus)
		{
			ptr = ptr->next;
			continue;
		}
		if (link->rm1 != start)
			room = link->rm1;
		else
			room = link->rm2;
		if (room->way_nbr < 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void		form_the_set_norm(t_intldta *indta, t_find_way *find, \
	t_form_set *fs)
{
	fs->ptr = find->ways;
	fs->i_min = 1;
	while (fs->ptr)
	{
		if (fs->ptr->status)
			fs->counter++;
		fs->ptr->steps = 0;
		fs->ptr->full_steps = 0;
		fs->ptr = fs->ptr->next;
	}
	while (fs->i < fs->counter)
	{
		fs->i++;
		fs->steps_count = count_set_steps(indta, find, fs->i);
		if (fs->i == 1 || fs->steps_count < fs->min_steps_count)
		{
			fs->min_steps_count = fs->steps_count;
			fs->i_min = fs->i;
		}
	}
}

static int	form_the_set(t_find_way *find, t_intldta *indta)
{
	t_form_set	fs;

	ft_bzero(&fs, sizeof(fs));
	form_the_set_norm(indta, find, &fs);
	if (fs.counter)
	{
		add_new_set(find, fs.i_min, indta);
		return (1);
	}
	return (0);
}

int			rec_finding(t_intldta *indta, t_find_way *find)
{
	if (find->crnt_set && ((PRE && CUR->steps > PRE->steps) ||
	!check_free_rooms(indta->start_room)))
		return (1);
	if (wide_search(&find, &indta))
		form_the_set(find, indta);
	return (0);
}
