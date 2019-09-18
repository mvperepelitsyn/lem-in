/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_finding_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:01:35 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 17:42:03 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		pre_count_set_steps(t_find_way *find, t_count_steps *c, int count)
{
	c->ptr = find->ways;
	c->pre_lems = 0;
	c->max_len = 0;
	c->i = 0;
	while (c->ptr && c->i < count)
	{
		while (c->ptr && !c->ptr->status)
			c->ptr = c->ptr->next;
		if (c->ptr)
		{
			c->pre_lems -= c->ptr->len_way - 1;
			if (c->max_len < c->ptr->len_way)
				c->max_len = c->ptr->len_way;
			c->i++;
			if (c->i < count)
				c->ptr = c->ptr->next;
		}
	}
}

long long	count_set_steps(t_intldta *indta, t_find_way *find, int count)
{
	t_count_steps	c;

	pre_count_set_steps(find, &c, count);
	c.pre_lems += count * c.max_len;
	if (c.pre_lems > indta->num_ants)
		c.ptr->full_steps = 0;
	else
	{
		c.steps = (double)(indta->num_ants - c.pre_lems) / (double)count;
		if (c.steps > (long long)c.steps)
			c.steps++;
		c.ptr->full_steps = (long long)c.steps;
	}
	c.ptr->steps = c.ptr->full_steps + c.max_len;
	return (c.ptr->steps);
}

void		add_new_set_norm(t_intldta *indta, t_find_way *find, \
	t_way_set *set, t_way *ptr)
{
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
	if (indta->v_flag)
		cpy_the_state(&indta, &set->links, &set->rooms);
}

void		add_new_set(t_find_way *find, int ways_cnt, t_intldta *indta)
{
	t_way_set	*set;
	t_way		*ptr;
	int			i;

	if (!(set = (t_way_set*)ft_memalloc(sizeof(t_way_set))))
		ft_malloc_error(NULL);
	set->ways_cnt = ways_cnt;
	ptr = find->ways;
	i = 0;
	while (ptr && i < ways_cnt)
	{
		if (ptr->status)
		{
			if (!ft_lstaddnext(&set->ways, (void*)&ptr, sizeof(ptr)))
				ft_malloc_error(NULL);
			i++;
		}
		if (i < ways_cnt)
			ptr = ptr->next;
	}
	add_new_set_norm(indta, find, set, ptr);
}
