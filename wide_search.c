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
		if (search != NULL && fill_search(fnd_way, &search, &searched, indta))
			fill_searched(&searched, &search);
		else
			break ;
	}
	if (!end_searched(&searched, &search, &tmp_way, indta))
		return (0);
	fill_the_way(&tmp_way, searched);
	free_search_ed(&search, &searched);
	return (1);
}