/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_finding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 12:59:54 by uhand             #+#    #+#             */
/*   Updated: 2019/08/19 17:24:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_way.h"

static int	check_free_links(t_list_rooms *start)
{
	t_list			*ptr;
	t_list_links	*link;

	if (!start->act_lnks)
		return (0);
	ptr = start->links;
	while (ptr)
	{
		link = (t_list_links*)ptr->content;
		if (link->status)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static void	count_set_steps(t_find_way *find, t_intldta *indta, t_way_set *set)
{
	//
}

static void	add_new_set(t_find_way *find, t_intldta *indta, int ways_cnt)
{
	t_way_set	*set;
	t_way		*ptr;

	if (!(set = (t_way_set*)malloc(sizeof(t_way_set))))
		ft_malloc_error();
	set->ways = NULL;
	set->next = NULL;
	set->ways_cnt = ways_cnt;
	ptr = find->ways;
	while (ptr)
		if (ptr->status)
			if (!ft_lstaddnext(&set->ways, &ptr, sizeof(ptr)))
				ft_malloc_error();
	count_set_steps(find, indta, set);
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
}

static int	check_set_load(t_find_way *find, t_intldta *indta)
{
	t_way	*ptr;
	int		counter;

	ptr = find->ways;
	counter = 0;
	while (ptr)
		if (ptr->status)
			counter++;
	if ((!CUR && counter) || (CUR && counter > CUR->ways_cnt))
	{
		add_new_set(find, indta, counter);
		return (1);
	}
	return (0);
}

int			rec_finding(t_intldta *indta, t_find_way *find)
{
	if (find->crnt_set->ways_cnt == indta->num_ants || (PRE && \
		CUR->steps > PRE->steps) || !check_free_links(indta->start_room))
		return (1);
	if (wide_search(find, indta))
	{
		if (!check_set_load(find, indta))
			return (rec_finding(indta, find));
	}
	return (0);
}
