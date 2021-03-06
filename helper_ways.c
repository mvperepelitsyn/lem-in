/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:18:43 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/15 17:18:48 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			lnks = *(t_list_links **)ptr->content;
			if ((lnks->rm1 == tmp->rooms && lnks->rm2 == tmp->next->rooms) ||
			(lnks->rm2 == tmp->rooms && lnks->rm1 == tmp->next->rooms))
			{
				lnks->way_nbr = tmp->way_nbr;
				break ;
			}
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}

void			fill_the_way(t_way **tmp_way, t_search *list)
{
	t_way	*tmp;

	tmp = *tmp_way;
	while (tmp->next)
		tmp = tmp->next;
	way_assignment(list);
	mark_the_way(list);
	tmp->rooms = ft_dllnew((void *)&(list->rooms), sizeof(t_list_rooms*));
	list = list->next;
	while (list->next != NULL)
	{
		ft_dlladdnextr(&(tmp->rooms), (void *)&(list->rooms),
				sizeof(t_list_rooms*));
		list = list->next;
	}
	ft_dlladdnextr(&(tmp->rooms), (void *)&(list->rooms),
			sizeof(t_list_rooms*));
	tmp->len_way = list->step_nbr;
	tmp->status = 1;
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
		lnks = *(t_list_links **)ptr1->content;
		if (((ft_strequ(rm_1->name, lnks->room1) && ft_strequ(room2->name,
				lnks->room2)) || (ft_strequ(room2->name, lnks->room1) &&
				ft_strequ(rm_1->name, lnks->room2))) && lnks->sttus == 1)
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
