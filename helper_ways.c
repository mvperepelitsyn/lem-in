//
// Created by Dwarven centurion Frost atronach on 2019-09-05.
//

#include "lem_in.h"

static	void	way_assignment(t_search *list)
{
	t_search *tmp;

	tmp = list;
	while (tmp)
	{
		tmp->rooms->way_nbr = (tmp->rooms->type == 0) ? tmp->way_nbr : -1;
		tmp->rooms->step_nbr = tmp->step_nbr;
		tmp = tmp->next;
	}
}

static	void	mark_the_way(t_search *list)
{
	t_search		*tmp;
	t_list			*ptr;
	t_list_links	*lnks;

	tmp = list;
	while (tmp)
	{
		ptr = tmp->rooms->links;
		while (tmp->rooms->type != 2)
		{
			lnks = ptr->content;
			if ((ft_strequ(lnks->room1, tmp->rooms->name) && ft_strequ(lnks->
					room2, tmp->next->rooms->name)) || (ft_strequ(lnks->room2, tmp->
					rooms->name) && ft_strequ(lnks->room1, tmp->next->rooms->name)))
			{
				lnks->way_nbr = tmp->way_nbr;
				break;
			}
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}

void	fill_the_way(t_way **tmp_way, t_search *list)
{
	make_it_clean(&list);
	way_assignment(list);
	mark_the_way(list);
	(*tmp_way)->rooms = ft_dllnew((void *)&(list->rooms),
								  sizeof(t_list_rooms*));
	list = list->next;
	while (list->next != NULL)
	{
		ft_dlladdnextr(&((*tmp_way)->rooms), (void *)&(list->rooms),
					   sizeof(t_list_rooms*));
		list = list->next;
	}
	ft_dlladdnextr(&((*tmp_way)->rooms), (void *)&(list->rooms),
				   sizeof(t_list_rooms*));
	(*tmp_way)->len_way = list->step_nbr;
	(*tmp_way)->status = 1;
	ft_printf("\nI find the way!");
	print_the_way(*tmp_way);
	ft_printf("\n-------------------\n");
}

int				it_has_link(t_list_rooms *room1, t_list_rooms *room2)
{
	t_list			*ptr1;
	t_list_links	*lnks;
	t_list_rooms	*rm_1;

	rm_1 = room1;
	ptr1 = rm_1->links;
	while (ptr1)
	{
		lnks = ptr1->content;
		if (((ft_strequ(rm_1->name, lnks->room1) && ft_strequ(room2->name,
				lnks->room2)) || (ft_strequ(room2->name, lnks->room1) &&
				ft_strequ(rm_1->name, lnks->room2))) && lnks->status == 1)
			return (1);
		ptr1 = ptr1->next;
	}
	return (0);
}

void			del_t_list_room(t_search **room)
{
	t_search *tmp;

	tmp = *room;
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	free(tmp);
	tmp = NULL;
}
