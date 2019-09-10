//
// Created by Dwarven centurion Frost atronach on 2019-09-05.
//

#include "lem_in.h"

static	void stop_search(t_find_way **find, t_list_links *lnks, t_list_rooms *rm,
		t_intldta **indta)
{
	if (ft_strequ(lnks->room1, rm->name) && lnks->rm2->way_nbr > 0 &&
		lnks->status == 1 && lnks->way_nbr < 0)
	{
		if (pre_link_breaker(find, lnks->rm2))
			return ;
		else
		{
			if ((*find)->check != 1)
			{
				wide_breaker(lnks, lnks->rm2);
				rev_wide_search(indta);
			}
		}
	}
	else if (ft_strequ(lnks->room2, rm->name) && lnks->rm1->way_nbr > 0 &&
			 lnks->status == 1 && lnks->way_nbr < 0)
	{
		if (pre_link_breaker(find, lnks->rm1))
			return ;
		else
		{
			if ((*find)->check != 1)
			{
				wide_breaker(lnks, lnks->rm2);
				rev_wide_search(indta);
			}
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
	char *name;

	name = (*srch)->rooms->name;
	if (ft_strequ(lnk->room1, name) && not_in_searched(lnk->room2, *srchd,
			*srch) && lnk->rm2->way_nbr < 0 && lnk->status == 1)
	{
		if (help_fill_search(&lnk->rm2, lnk->rm1, tmp))
			return (1);
		else if (ft_strequ(lnk->room2, name) && not_in_searched(lnk->room1,
			*srchd, *srch) && lnk->rm1-> way_nbr < 0 && lnk->status == 1)
		{
			if (help_fill_search(&lnk->rm1, lnk->rm2, tmp))
				return (1);
		}
	}
	else if (ft_strequ(lnk->room2, name) && not_in_searched(lnk->room1, *srchd,
			*srch) && lnk->rm1->way_nbr < 0 && lnk->status == 1)
	{
		if (help_fill_search(&lnk->rm1, lnk->rm2, tmp))
			return (1);
		else if (ft_strequ(lnk->room1, name) && not_in_searched(lnk->room2,
				*srchd, *srch) && lnk->rm2-> way_nbr < 0 && lnk->status == 1)
		{
			if (help_fill_search(&lnk->rm2, lnk->rm1, tmp))
				return (1);
		}
	}
	return (0);
}

static	void	cpy_t_searched(t_search **srchd, t_search **lst, t_list_links *end_lnk)
{
	t_search *tmp_l;
	t_search *tmp_d;

	*lst = (t_search *)ft_memalloc(sizeof(t_search));
	tmp_l = *lst;
	tmp_d = *srchd;
	while (tmp_d)
	{
		tmp_l->rooms = tmp_d->rooms;
		tmp_l->step_nbr = tmp_d->step_nbr;
		tmp_l->way_nbr = tmp_d->way_nbr;
		tmp_l->next = (t_search *)ft_memalloc(sizeof(t_search));
		tmp_l->next->prev = tmp_l;
		tmp_l = tmp_l->next;
		tmp_d = tmp_d->next;
	}
	tmp_l->rooms = (end_lnk->rm2->type == 2) ? end_lnk->rm1 : end_lnk->rm2;
	tmp_l->step_nbr = tmp_l->rooms->tmp_step_nbr;
	tmp_l->way_nbr = tmp_l->prev->way_nbr;
	tmp_l->next = (t_search *)ft_memalloc(sizeof(t_search));
	tmp_l->next->prev = tmp_l;
	tmp_l = tmp_l->next;
	tmp_l->rooms = (end_lnk->rm2->type == 2) ? end_lnk->rm2 : end_lnk->rm1;
	tmp_l->step_nbr = tmp_l->prev->step_nbr + 1;
	tmp_l->way_nbr = tmp_l->prev->way_nbr;
	make_it_clean(&tmp_l);
}

static	void	change_the_way_nbr(t_search **srch, t_search **srchd, int way_nbr)
{
	t_search *s1;
	t_search *s2;

	s1 = *srch;
	s2 = *srchd;
	while (s1)
	{
		if (s1->way_nbr > 0)
			s1->way_nbr = way_nbr;
		s1 = s1->next;
	}
	while (s2)
	{
		if (s2->way_nbr > 0)
			s2->way_nbr = way_nbr;
		s2 = s2->next;
	}
}

static	int 	check_the_way(t_search *lst)
{
	t_search *tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->rooms->way_nbr > 0)
			return (1);
		if (tmp->next && !it_has_link(tmp->rooms, tmp->next->rooms))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static	void	add_the_way(t_find_way **fnd, t_search **srch, t_search **srchd,
		t_list_links *end_lnk)
{
	t_way		*tmp;
	t_search	*lst;
	t_search	*trash;

	trash = NULL;
	cpy_t_searched(srchd, &lst, end_lnk);
	if (check_the_way(lst))
		return ;
	init_way(fnd);
	tmp = (*fnd)->ways;
	while (tmp->next)
		tmp = tmp->next;
	fill_the_way(&tmp, lst);
	free_search_ed(&lst, &trash);
	change_the_way_nbr(srch, srchd, give_me_way_nbr(&((*fnd)->ways)));
}

int			fill_search(t_find_way **fnd, t_search **srch, t_search **searched,
		t_intldta **indta)
{
	int num_lnks;
	t_list *ptr;
	t_list_links *pt_link;
	t_search *tmp;

	num_lnks = (*srch)->rooms->num_lnks;
	ptr = (*srch)->rooms->links;
	while (num_lnks != 0 || ptr != NULL)
	{
		tmp = *srch;
		pt_link = ptr->content;
//		if (tmp->rooms->act_lnks == 1 && tmp->rooms->type == 0)
//		{
//			dead_end_cleaner(tmp->rooms);
//			return (1);
//		}
		stop_search(fnd, pt_link, tmp->rooms, indta);
		if (help_fill_search2(pt_link, srch, searched, &tmp))
			add_the_way(fnd, srch, searched, pt_link);
		ptr = ptr->next;
		num_lnks--;
	}
	return (1);
}