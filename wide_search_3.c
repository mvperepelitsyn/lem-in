//
// Created by Dwarven centurion Frost atronach on 2019-09-05.
//

#include "lem_in.h"

static	int stop_search(t_find_way **find, t_list_links *lnks, t_list_rooms *rm)
{
	if (ft_strequ(lnks->room1, rm->name) && lnks->rm2->way_nbr > 0 &&
		lnks->status == 1 && lnks->way_nbr < 0)
	{
		if (link_breaker(find, lnks->rm2))
			return (1);
		else
			wide_breaker(lnks, lnks->rm1);
	}
	else if (ft_strequ(lnks->room2, rm->name) && lnks->rm1->way_nbr > 0 &&
			 lnks->status == 1 && lnks->way_nbr < 0)
	{
		if (link_breaker(find, lnks->rm1))
			return (1);
		else
			wide_breaker(lnks, lnks->rm2);
	}
	return (0);
}

static	int	help_fill_search(t_list_rooms **room, t_search **search,
		t_search **searched, t_search **tmp)
{
	while ((*tmp)->next != NULL)
		*tmp = (*tmp)->next;
	if ((*room)->type == 2)
	{
		fill_searched(searched, search);
		add_to_searched(searched, *room);
		return (1);
	}
	(*tmp)->next = (t_search *)ft_memalloc(sizeof(t_search));
	(*tmp)->next->prev = *tmp;
	(*tmp)->next->rooms = *room;
	(*tmp)->next->way_nbr = (*tmp)->way_nbr;
	(*tmp)->next->step_nbr = (*search)->step_nbr + 1;
	return (0);
}

static	int	help_fill_search2(t_list_links *lnk, t_search **srch, t_search
**srchd, t_search **tmp)
{
	char *name;

	name = (*srch)->rooms->name;
	if (ft_strequ(lnk->room1, name) && not_in_searched(lnk->room2, *srchd,
			*srch) && lnk->rm2->way_nbr < 0 && lnk->status == 1)
	{
		if (help_fill_search(&lnk->rm2, srch, srchd, tmp))
			return (1);
		else if (ft_strequ(lnk->room2, name) && not_in_searched(lnk->room1,
			*srchd, *srch) && lnk->rm1-> way_nbr < 0 && lnk->status == 1)
		{
			if (help_fill_search(&lnk->rm1, srch, srchd, tmp))
				return (1);
		}
	}
	else if (ft_strequ(lnk->room2, name) && not_in_searched(lnk->room1, *srchd,
			*srch) && lnk->rm1->way_nbr < 0 && lnk->status == 1)
	{
		if (help_fill_search(&lnk->rm1, srch, srchd, tmp))
			return (1);
		else if (ft_strequ(lnk->room1, name) && not_in_searched(lnk->room2,
				*srchd, *srch) && lnk->rm2-> way_nbr < 0 && lnk->status == 1)
		{
			if (help_fill_search(&lnk->rm2, srch, srchd, tmp))
				return (1);
		}
	}
	return (0);
}

int			fill_search(t_find_way **fnd, t_search **srch, t_search **searched)
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
		if (tmp->rooms->act_lnks == 1 && tmp->rooms->type == 0)
		{
			dead_end_cleaner(tmp->rooms);
			return (1);
		}
		if (stop_search(fnd, pt_link, tmp->rooms))
			return (0);
		if (help_fill_search2(pt_link, srch, searched, &tmp))
			return (0);
		ptr = ptr->next;
		num_lnks--;
	}
	return (1);
}
