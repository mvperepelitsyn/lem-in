/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_search_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:12:04 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/13 21:12:39 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	stop_search(t_find_way **find, t_list_links *lnks, t_list_rooms *rm,
		t_intldta **indta)
{
	(*indta)->ri = (*indta)->ri;
	if (lnks->rm1 == rm && lnks->rm2->way_nbr > 0 &&
		lnks->sttus == 1 && lnks->way_nbr < 0)
	{
		if (pre_link_breaker(find, lnks->rm2))
			return ;
		else
		{
			if ((*find)->check != 1)
				wide_breaker(lnks, lnks->rm2);
		}
	}
	else if (lnks->rm2 == rm && lnks->rm1->way_nbr > 0 && lnks->sttus == 1 &&
	lnks->way_nbr < 0)
	{
		if (pre_link_breaker(find, lnks->rm1))
			return ;
		else
		{
			if ((*find)->check != 1)
				wide_breaker(lnks, lnks->rm2);
		}
	}
}

static	int	help_fill_search(t_list_rooms **room, t_list_rooms *prev,
		t_search **tmp)
{
	while ((*tmp)->next != NULL)
		*tmp = (*tmp)->next;
	if ((*room)->type == 2)
		return (1);
	(*tmp)->next = (t_search *)ft_memalloc(sizeof(t_search));
	(*tmp)->next->prev = *tmp;
	(*tmp)->next->rooms = *room;
	(*tmp)->next->way_nbr = (*tmp)->way_nbr;
	(*room)->tmp_step_nbr = ((*room)->tmp_step_nbr == 0) ?
							(prev->tmp_step_nbr + 1) : (*room)->tmp_step_nbr;
	(*tmp)->next->step_nbr = (*room)->tmp_step_nbr;
	return (0);
}

static	int	help_fill_search2(t_list_links *lnk, t_search **srch, t_search
**srchd, t_search **tmp)
{
	if (lnk->rm1 == (*srch)->rooms && not_in_searched(lnk->rm2, *srchd, *srch)
		&& lnk->rm2->way_nbr < 0 && lnk->sttus == 1)
	{
		if (help_fill_search(&lnk->rm2, lnk->rm1, tmp))
			return (1);
		else if (lnk->rm2 == (*srch)->rooms && not_in_searched(lnk->rm1,
				*srchd, *srch) && lnk->rm1-> way_nbr < 0 && lnk->sttus == 1)
		{
			if (help_fill_search(&lnk->rm1, lnk->rm2, tmp))
				return (1);
		}
	}
	else if (lnk->rm2 == (*srch)->rooms && not_in_searched(lnk->rm1, *srchd,
			*srch) && lnk->rm1->way_nbr < 0 && lnk->sttus == 1)
	{
		if (help_fill_search(&lnk->rm1, lnk->rm2, tmp))
			return (1);
		else if (lnk->rm1 == (*srch)->rooms && not_in_searched(lnk->rm2,
				*srchd, *srch) && lnk->rm2-> way_nbr < 0 && lnk->sttus == 1)
		{
			if (help_fill_search(&lnk->rm2, lnk->rm1, tmp))
				return (1);
		}
	}
	return (0);
}

int			fill_search(t_find_way **fnd, t_search **srch, t_search **searched,
		t_intldta **indta)
{
	int				num_lnks;
	t_list			*ptr;
	t_list_links	**l;
	t_search		*tmp;

	num_lnks = (*srch)->rooms->num_lnks;
	ptr = (*srch)->rooms->links;
	while (num_lnks != 0 || ptr != NULL)
	{
		tmp = *srch;
		l = ptr->content;
		if ((*l)->sttus == 1 && tmp->rooms->act_lnks == 1 && tmp->rooms->type == 0)
		{
			dead_end_cleaner(tmp->rooms, 1);
			return (1);
		}
		stop_search(fnd, *l, tmp->rooms, indta);
		if (help_fill_search2(*l, srch, searched, &tmp))
			add_the_way(fnd, srch, searched, *l);
		if ((*fnd)->cnt_ways == (*fnd)->min_ways)
			return (0);
		ptr = ptr->next;
		num_lnks--;
	}
	return (1);
}
