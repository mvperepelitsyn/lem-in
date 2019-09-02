/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:26:05 by uhand             #+#    #+#             */
/*   Updated: 2019/09/02 16:40:40 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_cur_room(t_link_breaker *br, t_find_way **find, t_list_rooms
*room)
{
	br->way = find[0]->ways;
	while (br->way)
	{
		if (br->way->num_way == room->way_nbr)
			break ;
		br->way = br->way->next;
	}
	if (!br->way)
	{
		ft_printf("Bad way number!\n");
		ft_error();
	}
	br->wroom = br->way->rooms;
	while (br->wroom)
	{
		br->croom = (t_list_rooms **)br->wroom->content;
		if (ft_strequ(br->croom[0]->name, room->name))
			break ;
		br->wroom = br->wroom->right;
	}
	if (!br->wroom)
	{
		ft_printf("Bad room number!\n");
		ft_error();
	}
}

static int	check_connection(t_dllist *wroom)
{
	t_list_rooms	**croom;

	wroom = wroom->left;
	while (wroom)
	{
		croom = (t_list_rooms **)wroom->content;
		if (croom[0]->type == 0 && croom[0]->act_lnks > 2)
			return (1);
		else if (croom[0]->type == 1)
			return (0);
		wroom = wroom->left;
	}
	if (!wroom)
	{
		ft_printf("Wrong start of the way!\n");
		ft_error();
	}
	return (0);
}

static int	check_link(t_list_links	*link, t_list_rooms *croom, \
	t_list_rooms *prev_room)
{
	if ((ft_strequ(link->rm1->name, croom->name) && ft_strequ(link->rm2->name,
			prev_room->name)) || (ft_strequ(link->rm2->name, croom->name) &&
			ft_strequ(link->rm1->name, prev_room->name)))
		return (1);
	return (0);
}

static void	break_links(t_link_breaker *br)
{
	while (br->wroom)
	{
		br->prev_room = (t_list_rooms **)(br->wroom->left->content);
		br->link_ptr = br->croom[0]->links;
		while (br->link_ptr)
		{
			br->link = br->link_ptr->content;
			if (check_link(br->link, br->croom[0], br->prev_room[0]))
				break ;
			br->link_ptr = br->link_ptr->next;
		}
		if (!br->link_ptr)
		{
			ft_printf("Wrong links set!\n");
			ft_error();
		}
		br->link->status = 0;
		br->croom[0]->act_lnks--;
		if (br->prev_room[0]->act_lnks > 2)
		{
			br->prev_room[0]->act_lnks--;
			break ;
		}
		br->prev_room[0]->act_lnks--;
		br->wroom = br->wroom->left;
	}
}

//TODO LIST: link_breaker changes status of the link, BUT does not change the state of rooms

int			link_breaker(t_find_way **find, t_list_rooms *room)
{
	t_link_breaker	br;

	find_cur_room(&br, find, room);
	if (!check_connection(br.wroom))
		return (0);
	//test
//	while ((*find)->ways->rooms)
//	{
//		tmp = (*find)->ways->rooms->content;
//		tmp->status = 69;
//		(*find)->ways->rooms = (*find)->ways->rooms->right;
//	}

	break_links(&br);
	br.way->status = 0;
	br.wroom = br.way->rooms;
	while (br.wroom)
	{
		br.croom = (t_list_rooms **)br.wroom->content;
		br.croom[0]->way_nbr = -1;
		br.croom[0]->step_nbr = (br.croom[0]->type != 1) ? -1 : 0;
		br.link_ptr = br.croom[0]->links;
		while (br.link_ptr)
		{
			br.link = (t_list_links *)br.link_ptr->content;
			if (br.link->way_nbr == room->way_nbr)
				br.link->way_nbr = -1;
			br.link_ptr = br.link_ptr->next;
		}
		br.wroom = br.wroom->right;
	}
	return (1);
}

void	wide_breaker(t_list_links *link, t_list_rooms *room)
{
	t_wide_breaker	wr;

	link->status = 0;
	ft_printf("%p - incoming addr\n", link);//debug mode
	if (room->type == 1 || room->act_lnks != 2)
	{
		room->act_lnks--;
		return ;
	}
	room->act_lnks--;
	wr.link_ptr = room->links;
	while (wr.link_ptr)
	{
		wr.prev_link = (t_list_links*)wr.link_ptr->content;
		ft_printf("%p\n", wr.prev_link);//debug mode
		if (link != wr.prev_link)
			break ;
		wr.link_ptr = wr.link_ptr->next;
	}
	if (ft_strequ(room->name, wr.prev_link->room1))
		wr.prev_room = wr.prev_link->rm2;
	else
		wr.prev_room = wr.prev_link->rm1;
	wide_breaker(wr.prev_link, wr.prev_room);
}

//int			link_breaker(t_find_way **find, t_list_rooms *room)
//{
//	t_link_breaker	br;
//	t_way			*tmp;
//	t_list_rooms	*tmp2;
//
//	tmp = (*find)->ways;
//	find_cur_room(&br, find, room);
//	if (!check_connection(br.wroom))
//		return (0);
//	break_links(&br);
//	while (tmp->num_way != br.way->num_way)
//		tmp = tmp->next;
//	br.wroom = br.way->rooms;
//	while (tmp->rooms)
//	{
//		tmp2 = tmp->rooms->content;
//		tmp2->way_nbr = -1;
//		tmp2->step_nbr = (tmp2->type != 1) ? -1 : 0;
//		tmp->rooms = tmp->rooms->right;
//	}
//	return (1);
//}
