/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:01:47 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/17 19:32:11 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_link(t_list_links *link, t_list_rooms *croom, t_list_rooms
*prev_room)
{
	if ((link->rm1 == croom && link->rm2 == prev_room) || (link->rm2 == croom
	&& link->rm1 == prev_room))
		return (1);
	return (0);
}

void		break_links(t_link_breaker *br)
{
	while (br->wroom->left)
	{
		br->croom = (t_list_rooms **)br->wroom->content;
		br->prev_room = (t_list_rooms **)(br->wroom->left->content);
		br->link_ptr = br->croom[0]->links;
		while (br->link_ptr)
		{
			br->link = *(t_list_links **)br->link_ptr->content;
			if (check_link(br->link, br->croom[0], br->prev_room[0]))
				break ;
			br->link_ptr = br->link_ptr->next;
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

void		dead_end_cleaner(t_list_rooms *room, int prm)
{
	t_list			*link_ptr;
	t_list_links	*link;

	link = NULL;
	if (room->type != 0 || (room->act_lnks != 2 && !prm))
	{
		room->act_lnks--;
		return ;
	}
	link_ptr = room->links;
	while (link_ptr)
	{
		link = *(t_list_links **)link_ptr->content;
		if (link->sttus)
			break ;
		link_ptr = link_ptr->next;
	}
	link->sttus = 0;
	room->act_lnks = 0;
	//room->status = 0;
	if (room == link->rm1)
		room = link->rm2;
	else if (room == link->rm2)
		room = link->rm1;
	dead_end_cleaner(room, 0);
}

void		find_cur_room(t_link_breaker *br, t_find_way **find,
		t_list_rooms *room)
{
	br->way = find[0]->ways;
	while (br->way)
	{
		if (br->way->num_way == room->way_nbr)
			break ;
		br->way = br->way->next;
	}
	br->wroom = br->way->rooms;
	while (br->wroom)
	{
		br->croom = (t_list_rooms **)br->wroom->content;
		if (br->croom[0] == room)
			break ;
		br->wroom = br->wroom->right;
	}
}
