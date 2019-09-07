//
// Created by Dwarven centurion Frost atronach on 2019-09-04.
//

#include "lem_in.h"

static	void	del_t_way(t_way **way)
{
	if ((*way)->next == NULL && (*way)->prev == NULL)
	{
		free(*way);
		*way = NULL;
	}
	else
	{
		*way = (*way)->prev;
		free((*way)->next);
		(*way)->next = NULL;
	}
}

static int		end_searched(t_search **searched, t_search **search, t_way
**wy, t_intldta **indta)
{
	t_search *tmp;

	tmp = *searched;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->rooms->type == 2)
		return (1);
	free_search_ed(search, searched);
	del_t_way(wy);
	rev_wide_search(indta);
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

//static	void	init_search(t_wide_search **ws, t_intldta **indta, t_way *tmp_w)
//{
//	(*ws)->search = (t_search *)ft_memalloc(sizeof(t_search));
//	(*ws)->searched = (t_search *)ft_memalloc(sizeof(t_search));
//	(*ws)->search->rooms = (*indta)->start_room;
//	(*ws)->search->step_nbr = 0;
//	(*ws)->search->way_nbr = tmp_w->num_way;
//}

int		wide_search(t_find_way **fnd_way, t_intldta **indta)
{
	t_search		*srch;
	t_search		*srched;
	t_way			*tmp_way;

	init_way(fnd_way);
	tmp_way = (*fnd_way)->ways;
	while (tmp_way->next != NULL)
		tmp_way = tmp_way->next;
	srch = (t_search *)ft_memalloc(sizeof(t_search));
	srched = (t_search *)ft_memalloc(sizeof(t_search));
	srch->rooms = (*indta)->start_room;
	srch->step_nbr = 0;
	srch->way_nbr = tmp_way->num_way;
	while (1)
	{
		if (srch != NULL && fill_search(fnd_way, &srch, &srched, indta))
			fill_searched(&srched, &srch);
		else
			break ;
	}
	if (!end_searched(&srched, &srch, &tmp_way, indta) && link_breaker(fnd_way))
		return (0);
	(*fnd_way)->del_room = NULL;
	fill_the_way(&tmp_way, srched);
	free_search_ed(&srch, &srched);
	return (1);
}