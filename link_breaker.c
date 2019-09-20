/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:26:05 by uhand             #+#    #+#             */
/*   Updated: 2019/09/16 10:00:30 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int			pre_link_breaker(t_find_way **fnd, t_list_rooms *room)
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

static int	help_link_breaker(t_link_breaker *br, t_find_way **find)
{
	if ((*find)->del_room == NULL)
		return (1);
	find_cur_room(br, find, (*find)->del_room);
	break_links(br);
	br->way->status = 0;
	br->room_nbr = (*find)->del_room->way_nbr;
	br->wroom = br->way->rooms;
	return (0);
}

int			link_breaker(t_find_way **find)
{
	t_link_breaker	br;

	if (help_link_breaker(&br, find))
		return (0);
	while (br.wroom)
	{
		br.croom = (t_list_rooms **)br.wroom->content;
		br.croom[0]->way_nbr = -1;
		br.croom[0]->step_nbr = (br.croom[0]->type != 1) ? -1 : 0;
		br.link_ptr = br.croom[0]->links;
		while (br.link_ptr)
		{
			br.link = *(t_list_links **)br.link_ptr->content;
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
