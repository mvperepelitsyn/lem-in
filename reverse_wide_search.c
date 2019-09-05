//
// Created by Dwarven centurion Frost atronach on 2019-09-05.
//

#include "lem_in.h"

static	void	set_start_status(t_list_rooms *start)
{
	t_list			*ptr;
	t_list_links	*pt_lnk;

	ptr = start->links;
	while (ptr)


}

int		rev_wide_search(t_find_way **fnd_way, t_intldta **indta)
{
	t_search	*search;
	t_search	*searched;

	search = (t_search *)ft_memalloc(sizeof(t_search));
	searched = (t_search *)ft_memalloc(sizeof(t_search));
	search->rooms = (*indta)->end_room;
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