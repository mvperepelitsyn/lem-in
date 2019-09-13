/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:26:05 by uhand             #+#    #+#             */
/*   Updated: 2019/09/13 12:16:04 by uhand            ###   ########.fr       */
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
		if (br->croom[0] == room)
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
	if ((link->rm1 == croom && link->rm2 == prev_room) || (link->rm2 == croom \
		&& link->rm1 == prev_room))
	 	return (1);
	return (0);
}

static void	break_links(t_link_breaker *br)
{
	while (br->wroom->left)
	{
		br->croom = (t_list_rooms **)br->wroom->content;
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
		br->link->sttus = 0;
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

int 		pre_link_breaker(t_find_way **fnd, t_list_rooms *room)
{
	t_link_breaker br;

	find_cur_room(&br, fnd, room);
	if (check_connection(br.wroom))
	{
		if ((*fnd)->del_room == NULL)
			(*fnd)->del_room = room;
		return (1);
	}
	return (0);
}

int			link_breaker(t_find_way **find)
{
	t_link_breaker	br;

	if ((*find)->del_room == NULL)
		return (0);
	find_cur_room(&br, find, (*find)->del_room);
	break_links(&br);
	br.way->status = 0;
	br.room_nbr = (*find)->del_room->way_nbr;
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
			if (br.link->way_nbr == br.room_nbr)
			{
				br.link->way_nbr = -1;
				break ;
			}
			br.link_ptr = br.link_ptr->next;
		}
		br.wroom = br.wroom->right;
	}
	return (1);
}

void	wide_breaker(t_list_links *link, t_list_rooms *room)
{
	t_wide_breaker	wr;

	link->sttus = 0;
	if (room == link->rm2)
		link->rm1->act_lnks--;
	else
		link->rm2->act_lnks--;
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
		if (wr.prev_link->sttus)
			break ;
		wr.link_ptr = wr.link_ptr->next;
	}
	if (room == wr.prev_link->rm1)
		wr.prev_room = wr.prev_link->rm2;
	else
		wr.prev_room = wr.prev_link->rm1;
	wide_breaker(wr.prev_link, wr.prev_room);
}

void	dead_end_cleaner(t_list_rooms *room, int prm)
{
	t_list			*link_ptr;
	t_list_links	*link;

	if (room->type != 0 || (room->act_lnks != 2 && !prm))
	{
		room->act_lnks--;
		return ;
	}
	link_ptr = room->links;
	while (link_ptr)
	{
		link = (t_list_links*)link_ptr->content;
		if (link->sttus)
			break ;
		link_ptr = link_ptr->next;
	}
	if (!link_ptr)
	{
		ft_printf("dead_end_cleaner error\n");
		ft_error();
	}
	link->sttus = 0;
	room->act_lnks = 0;
	if (room == link->rm1)
		room = link->rm2;
	else if (room == link->rm2)
		room = link->rm1;
	else
		ft_printf("dead_end_cleaner debug message\n");
	dead_end_cleaner(room, 0);
}
