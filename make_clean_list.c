//
// Created by Dwarven centurion Frost atronach on 2019-09-05.
//

#include "lem_in.h"

static	int		make_it_clean_help2(t_search **tmp, t_search **tmp2, int i)
{
	if (i == 1)
		if (((*tmp)->step_nbr >= (*tmp)->next->step_nbr) || !it_has_link((*tmp)
		->rooms, (*tmp)->next->rooms) || !it_has_link((*tmp)->rooms, (*tmp)->
		prev->rooms))
			return (1);
	if (i == 2)
		if (!it_has_link((*tmp)->rooms, (*tmp)->prev->rooms) && ((*tmp)
		->step_nbr + 1) == (*tmp)->next->step_nbr && it_has_link((*tmp)->rooms,
				(*tmp)->next->rooms))
			return (1);
	if (i == 3)
		if (it_has_link((*tmp)->rooms, (*tmp2)->rooms) && (*tmp2)->step_nbr <
		        (*tmp)->step_nbr)
			return (1);
	return (0);
}

static	void	make_it_clean_help4(t_search **tmp, t_search **tmp2, int *cnt)
{
	*cnt = 1;
	*tmp2 = (*tmp2)->next;
	while (!ft_strequ((*tmp2)->rooms->name, (*tmp)->rooms->name))
	{
		del_t_list_room(tmp2);
		*tmp2 = (*tmp2)->next;
	}
}

static	void	make_it_clean_help3(t_search **tmp, t_search **tmp2, int *cnt)
{
	while ((*tmp2)->prev != NULL)
	{
		if (make_it_clean_help2(tmp, tmp2, 3))
		{
			make_it_clean_help4(tmp, tmp2, cnt);
			break;
		}
		*tmp2 = (*tmp2)->prev;
	}
}


static	void 	make_it_clean_help(t_search **tmp, t_search **tmp2, int *cnt)
{
	while ((*tmp)->prev != NULL)
	{
		*cnt = 0;
		if (make_it_clean_help2(tmp, tmp2, 1))
		{
			if (make_it_clean_help2(tmp, tmp2, 2))
			{
				*tmp2 = (*tmp)->prev;
				make_it_clean_help3(tmp, tmp2, cnt);
				if ((*tmp2)->prev == NULL)
				{
					if (make_it_clean_help2(tmp, tmp2, 3))
					{
						make_it_clean_help4(tmp, tmp2, cnt);
						break;
					}
					*tmp2 = (*tmp2)->prev;
				}
			}
			if (*cnt == 0)
				del_t_list_room(tmp);
		}
		*tmp = (*tmp)->prev;
	}
}

void			make_it_clean(t_search **lst_rooms)
{
	t_search	*tmp;
	t_search	*tmp2;
	int 		cnt;

	cnt = 0;
	tmp = *lst_rooms;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp = tmp->prev;
	make_it_clean_help(&tmp, &tmp2, &cnt);
}