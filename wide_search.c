//
// Created by Dwarven centurion Frost atronach on 2019-09-04.
//

#include "lem_in.h"

static	void	del_t_way(t_way **way)
{
	*way = (*way)->prev;
	free((*way)->next);
	(*way)->next = NULL;
}

static	void	free_search_ed(t_search **search, t_search **searched)
{
	if ((*search) != NULL)
	{
		while ((*search)->prev != NULL)
			*search = (*search)->prev;
		while ((*search)->next != NULL)
		{
			(*search) = (*search)->next;
			free((*search)->prev);
			(*search)->prev = NULL;
		}
		if ((*search)->prev != NULL)
		{
			free((*search)->prev);
			(*search)->prev = NULL;
		}
		free(*search);
		*search = NULL;
	}
	if (*searched != NULL)
		free_search_ed(searched, search);

}

static	int 	not_in_searched(char *room, t_search *searched, t_search *search)
{
	t_search *check;
	t_search *check2;

	check = searched;
	check2 = search;
	if (searched->rooms == NULL)
		return (1);
	else
	{
		while (check != NULL)
		{
			if (ft_strequ(room, check->rooms->name))
				return (0);
			check = check->next;
		}
		while (check2 != NULL)
		{
			if (ft_strequ(room, check2->rooms->name))
				return (0);
			check2 = check2->next;
		}
		return (1);
	}
}

static	int stop_search(t_find_way **find, t_list_links *lnks, t_list_rooms *room)
{
	if (ft_strequ(lnks->room1, room->name) && lnks->rm2->way_nbr > 0 && lnks->status == 1 && lnks->way_nbr < 0)
	{
		if (link_breaker(find, lnks->rm2))
			return (1);
		else
			wide_breaker(lnks, lnks->rm1);
	}
	else if (ft_strequ(lnks->room2, room->name) && lnks->rm1->way_nbr > 0 && lnks->status == 1 && lnks->way_nbr < 0)
	{
		if (link_breaker(find, lnks->rm1))
			return (1);
		else
			wide_breaker(lnks, lnks->rm2);
	}
	return (0);
}

static	void	add_to_searched(t_search **searched, t_list_rooms *end_room)
{
	t_search	*srd;
	int 		stp_nbr;

	srd = *searched;
	while (srd->next != NULL)
		srd = srd->next;
	stp_nbr = srd->step_nbr + 1;
	srd->next = (t_search *)ft_memalloc(sizeof(t_search));
	srd->next->prev = srd;
	srd->next->rooms = end_room;
	srd->next->way_nbr = -1;
	srd->next->step_nbr = stp_nbr + 1;
}

static	int		help_fill_search(t_list_rooms **room, t_search **search,
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

static	int help_fill_search2(t_list_links *lnk, t_search **search, t_search
**searched, t_search **tmp)
{
	char *name;

	name = (*search)->rooms->name;
	if (ft_strequ(lnk->room1, name) && not_in_searched(lnk-> room2, *searched,
			*search) && lnk->rm2->way_nbr < 0 && lnk->status == 1)
		if (help_fill_search(&lnk->rm2, search, searched, tmp))
			return (1);
	else if (ft_strequ(lnk->room2, name) && not_in_searched(lnk->room1,
				*searched, *search) && lnk->rm1-> way_nbr < 0 && lnk->status ==
				1)
		if (help_fill_search(&lnk->rm1, search, searched, tmp))
			return (1);
	return (0);
}

static	int	fill_search(t_find_way **find, t_search **search, t_search **searched)
{
	int				num_lnks;
	t_list			*ptr;
	t_list_links	*pt_link;
	t_search		*tmp;

	num_lnks = (*search)->rooms->num_lnks;
	ptr = (*search)->rooms->links;
	while (num_lnks != 0 || ptr != NULL)
	{
		tmp = *search;
		pt_link = ptr->content;
		if (tmp->rooms->act_lnks == 1 && tmp->rooms->type == 0)
		{
			dead_end_cleaner(tmp->rooms);
			return (1);
		}
		if (stop_search(find, pt_link, tmp->rooms))
			return (0);
		if (help_fill_search2(pt_link, search, searched, &tmp))
			return (0);
		ptr = ptr->next;
		num_lnks--;
	}
	return (1);
}

static	void		help_fill_searched(t_search **s1, t_search **s2)
{
	if ((*s2)->step_nbr == 0)
	{
		(*s1)->rooms = (*s2)->rooms;
		(*s1)->way_nbr = (*s2)->way_nbr;
		(*s1)->step_nbr = (*s2)->step_nbr;
	}
	else
	{
		while ((*s1)->next != NULL)
			*s1 = (*s1)->next;
		(*s1)->next = (t_search *)ft_memalloc(sizeof(t_search));
		(*s1)->next->prev = *s1;
		(*s1)->next->rooms = (*s2)->rooms;
		(*s1)->next->way_nbr = (*s2)->way_nbr;
		(*s1)->next->step_nbr = (*s2)->step_nbr;
	}
}

void			fill_searched(t_search **searched, t_search **search)
{
	t_search	*s1;
	t_search	*s2;
//TODO: IF ALL THE ROOMS IN LINKS OF THE ROOM THAT WE WANT TO ADD HAVE STATUS 1 THEN WE DO NOT ADD IT TO THE LIST OF SEARCHED
	s1 = *searched;
	s2 = *search;
	help_fill_searched(&s1, &s2);
	if ((*search)->next != NULL)
	{
		*search = (*search)->next;
		free(s2);
		s2 = NULL;
		(*search)->prev = NULL;
	}
	else
	{
		free(*search);
		*search = NULL;
	}
}

static int		end_searched(t_search **searched, t_search **search, t_way **wy)
{
	t_search *tmp;

	tmp = *searched;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->rooms->type == 2)
		return (1);
	free_search_ed(search, searched);
	del_t_way(wy);
	return (0);
}

static	void	init_way(t_find_way **fnd_way)
{
	t_way	*tmp_way;

	if ((*fnd_way)->ways == NULL)
	{
		(*fnd_way)->ways = (t_way *)ft_memalloc(sizeof(t_way));
		tmp_way = (*fnd_way)->ways;
		tmp_way->next = NULL;
		tmp_way->status = 1;
		tmp_way->prev = NULL;
		tmp_way->num_way = 1;
	}
	else
	{
		tmp_way = (*fnd_way)->ways;
		while (tmp_way->next != NULL)
			tmp_way = tmp_way->next;
		tmp_way->next = (t_way *)malloc(sizeof(t_way));
		tmp_way->next->prev = (tmp_way);
		tmp_way->next->status = 1;
		tmp_way->next->num_way = tmp_way->num_way + 1;
		tmp_way->next->next = NULL;
		tmp_way = tmp_way->next;
	}
}

int		wide_search(t_find_way **fnd_way, t_intldta **indta)
{
	t_search	*search;
	t_search	*searched;
	t_way		*tmp_way;

	init_way(fnd_way);
	tmp_way = (*fnd_way)->ways;
	while (tmp_way->next != NULL)
		tmp_way = tmp_way->next;
	search = (t_search *)ft_memalloc(sizeof(t_search));
	searched = (t_search *)ft_memalloc(sizeof(t_search));
	search->rooms = (*indta)->start_room;
	search->step_nbr = 0;
	search->way_nbr = tmp_way->num_way;
	while (1)
	{
		if (search != NULL && fill_search(fnd_way, &search, &searched))
			fill_searched(&searched, &search);
		else
			break ;
	}
	if (!end_searched(&searched, &search, &tmp_way))
		return (0);
	fill_the_way(&tmp_way, searched);
	free_search_ed(&search, &searched);
	return (1);
}