/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:22:53 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/13 19:32:02 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			give_me_way_nbr(t_way **ways)
{
	t_way	*tmp_way;
	int		tmp;

	tmp = 1;
	if (*ways == NULL)
		return (tmp);
	else
	{
		tmp_way = *ways;
		while (tmp_way)
		{
			if (tmp_way->num_way > tmp)
				tmp = tmp_way->num_way;
			tmp_way = tmp_way->next;
		}
		return (tmp + 1);
	}
}

void		insert_way(t_find_way *find, t_way *way)
{
	t_way	*ptr;
	t_way	*prev;

	if (!find->ways)
	{
		find->ways = way;
		return ;
	}
	ptr = find->ways;
	prev = ptr->prev;
	while (ptr)
	{
		if (ptr->len_way > way->len_way)
			break ;
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr)
	{
		ptr->prev = way;
		way->next = ptr;
	}
	prev->next = way;
	way->prev = prev;
}

static void	init_search_searched(t_find_way **fnd_way, t_intldta **indta,
		t_search **srch, t_search **srched)
{
	*srch = (t_search *)ft_memalloc(sizeof(t_search));
	*srched = (t_search *)ft_memalloc(sizeof(t_search));
	(*srch)->rooms = (*indta)->start_room;
	(*srch)->step_nbr = 0;
	(*fnd_way)->min_ways = 0;
	(*fnd_way)->cnt_ways = 0;
	(*fnd_way)->check_2 = give_me_way_nbr(&((*fnd_way)->ways));
	(*fnd_way)->min_ways = ((*indta)->start_room->act_lnks > (*indta)->end_room
			->act_lnks) ? (*indta)->end_room->act_lnks : (*indta)->start_room->
					act_lnks;
	(*srch)->way_nbr = (*fnd_way)->check_2;
}

int			wide_search(t_find_way **fnd_way, t_intldta **indta)
{
	t_search		*srch;
	t_search		*srched;

	init_search_searched(fnd_way, indta, &srch, &srched);
	while (1)
	{
		if (srch != NULL && fill_search(fnd_way, &srch, &srched, indta))
			fill_searched(&srched, &srch);
		else
			break ;
	}
	if ((*fnd_way)->check_2 == give_me_way_nbr((&(*fnd_way)->ways)))
	{
		if (!link_breaker(fnd_way))
			rev_wide_search(indta);
		(*fnd_way)->check_2 = 0;
	}
	erase_tmp_step_nbr((*indta)->rooms);
	(*fnd_way)->del_room = NULL;
	free_search_ed(&srch, &srched);
	(*fnd_way)->check++;
	return (((*fnd_way)->check_2 == 0) ? 0 : 1);
}
