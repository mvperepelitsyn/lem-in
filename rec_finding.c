/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_finding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:59:54 by uhand             #+#    #+#             */
/*   Updated: 2019/09/09 17:09:11 by uhand            ###   ########.fr       */
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
		link = (t_list_links*)ptr->content;
		if (!link->status)
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

static int	count_set_steps(t_intldta *indta, t_find_way *find, int count)
{
	t_count_steps	c;

	c.ptr = find->ways;
	c.pre_lems = 0;
	c.max_len = 0;
	c.i = 0;
	while (c.ptr && c.i < count)
	{
		while (c.ptr && !c.ptr->status)
			c.ptr = c.ptr->next;
		if (c.ptr)
		{
			c.pre_lems -= c.ptr->len_way - 1;
			if (c.max_len < c.ptr->len_way)
				c.max_len = c.ptr->len_way;
			c.i++;
			if (c.i < count)
				c.ptr = c.ptr->next;
		}
	}
	if (c.i != count)
		ft_printf("count steps error!\n");
	c.pre_lems += count * c.max_len;
	if (c.pre_lems > indta->num_ants)
		c.ptr->full_steps = -1;
	else
	{
		c.steps = (indta->num_ants - c.pre_lems) / count;
		if (c.steps > (int)c.steps/* && !(indta->num_ants == c.pre_lems)*/)
			c.steps++;
		c.ptr->full_steps = (int)c.steps;
	}
	c.ptr->steps = c.ptr->full_steps + c.max_len;
	return (c.ptr->steps);
}

void		print_the_set(t_way_set *set)
{
	t_list	*tmp;
	t_way	**ptr;

	tmp = set->ways;
	ft_printf("\nHere is the set of ways, that we found:\n");
	ft_printf("\nThe number of steps %d\n", set->steps);
	while (tmp)
	{
		ptr = tmp->content;
		print_the_way(*ptr);
		tmp = tmp->next;
	}
	ft_printf("\n-------------------\n");
}

static void	add_new_set(t_find_way *find, int ways_cnt)
{
	t_way_set	*set;
	t_way		*ptr;
	int			i;

	if (!(set = (t_way_set*)ft_memalloc(sizeof(t_way_set))))
		ft_malloc_error();
	set->ways_cnt = ways_cnt;
	ptr = find->ways;
	i = 0;
	while (ptr && i < ways_cnt)
	{
		if (ptr->status)
			if (!ft_lstaddnext(&set->ways, (void*)&ptr, sizeof(ptr)))
				ft_malloc_error();
		i++;
		if (i < ways_cnt)
			ptr = ptr->next;
	}
	set->full_steps = ptr->full_steps;
	set->steps = ptr->steps;
	if (!CUR)
		set->prev = NULL;
	else
	{
		set->prev = CUR;
		CUR->next = set;
	}
	CUR = set;
	if (!find->sets)
		find->sets = find->crnt_set;
	print_the_set(find->crnt_set);
}

static int	form_the_set(t_find_way *find, t_intldta *indta)
{
	t_form_set	fs;

	ft_bzero(&fs, sizeof(fs));
	fs.ptr = find->ways;
	fs.i_min = 1;
	while (fs.ptr)
	{
		if (fs.ptr->status)
			fs.counter++;
		fs.ptr->steps = 0;
		fs.ptr->full_steps = 0;
		fs.ptr = fs.ptr->next;
	}
	while (fs.i < fs.counter)
	{
		fs.i++;
		fs.steps_count = count_set_steps(indta, find, fs.i);
		if (fs.i == 1 || fs.steps_count < fs.min_steps_count)
		{
			fs.min_steps_count = fs.steps_count;
			fs.i_min = fs.i;
		}
	}
	if (fs.counter)
	{
		add_new_set(find, fs.i_min);
		return (1);
	}
	return (0);
}

int			rec_finding(t_intldta *indta, t_find_way *find)
{
	if (find->crnt_set && (/*find->crnt_set->ways_cnt == indta->num_ants || \
		CUR->full_steps == -1 || (PRE && CUR->steps > PRE->steps) || \
		*/ !check_free_rooms(indta->start_room)))
		return (1);
	wide_search(&find, &indta);
	form_the_set(find, indta);
	/*if (wide_search(&find, &indta))
	{
		if (!check_set_load(find, indta))
			return (rec_finding(indta, find));
	}*/
	return (0);
}
