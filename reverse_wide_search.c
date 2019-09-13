/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_wide_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:23:09 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/13 21:31:54 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_start_status(t_list_rooms *start)
{
	t_list			*ptr;
	t_list_links	*pt_lnk;

	ptr = start->links;
	while (ptr)
	{
		pt_lnk = ptr->content;
		pt_lnk->sttus = (pt_lnk->way_nbr < 0) ? 0 : pt_lnk->sttus;
		pt_lnk->rm1->act_lnks--;
		pt_lnk->rm2->act_lnks--;
		ptr = ptr->next;
	}
}

static	int		rev_help_fill_search(t_list_rooms **room, t_list_links *lnk,
		t_search **search, t_search **tmp)
{
	while ((*tmp)->next != NULL)
		*tmp = (*tmp)->next;
	if ((*room)->type == 1)
	{
		lnk->rm1->act_lnks++;
		lnk->rm2->act_lnks++;
		return (1);
	}
	(*tmp)->next = (t_search *)ft_memalloc(sizeof(t_search));
	(*tmp)->next->prev = *tmp;
	(*tmp)->next->rooms = *room;
	(*tmp)->next->step_nbr = (*search)->step_nbr + 1;
	return (0);
}

static	int		rev_help_fill_search2(t_list_links *lnk, t_search **srch,
		t_search **srchd, t_search **tmp)
{
	if ((lnk->rm1 == (*srch)->rooms) && not_in_searched(lnk->rm2, *srchd, *srch)
	&& (lnk->sttus == 1 || lnk->rm2->type == 1))
	{
		if (rev_help_fill_search(&lnk->rm2, lnk, srch, tmp))
			lnk->sttus = 1;
		else if (lnk->rm2 == (*srch)->rooms && not_in_searched(lnk->rm1,
				*srchd, *srch) && lnk->rm1-> way_nbr < 0)
		{
			if (rev_help_fill_search(&lnk->rm1, lnk, srch, tmp))
				lnk->sttus = 1;
		}
	}
	else if (lnk->rm2 == (*srch)->rooms && not_in_searched(lnk->rm1, *srchd,
			*srch) && (lnk->sttus == 1 || lnk->rm1->type == 1))
	{
		if (rev_help_fill_search(&lnk->rm1, lnk, srch, tmp))
			lnk->sttus = 1;
		else if (lnk->rm1 == (*srch)->rooms && not_in_searched(lnk->rm2,
				*srchd, *srch) && lnk->rm2-> way_nbr < 0)
		{
			if (rev_help_fill_search(&lnk->rm2, lnk, srch, tmp))
				lnk->sttus = 1;
		}
	}
	return (0);
}

static	int		rev_fill_search(t_search **srch, t_search **srchd)
{
	int				num_lnks;
	t_list			*ptr;
	t_list_links	*pt_link;
	t_search		*tmp;

	num_lnks = (*srch)->rooms->num_lnks;
	ptr = (*srch)->rooms->links;
	while (num_lnks != 0 || ptr != NULL)
	{
		tmp = *srch;
		pt_link = ptr->content;
		if (rev_help_fill_search2(pt_link, srch, srchd, &tmp))
			return (0);
		ptr = ptr->next;
		num_lnks--;
	}
	return (1);
}

int				rev_wide_search(t_intldta **indta)
{
	t_search	*search;
	t_search	*searched;
	int			act_links_b;

	(*indta)->counter++;
	act_links_b = (*indta)->start_room->act_lnks;
	set_start_status((*indta)->start_room);
	search = (t_search *)ft_memalloc(sizeof(t_search));
	searched = (t_search *)ft_memalloc(sizeof(t_search));
	search->rooms = (*indta)->end_room;
	search->step_nbr = 0;
	while (1)
	{
		if (act_links_b == (*indta)->start_room->act_lnks)
			break ;
		if (search != NULL && rev_fill_search(&search, &searched))
			rev_fill_searched(&searched, &search);
		else
			break ;
	}
	free_search_ed(&search, &searched);
	return (1);
}
