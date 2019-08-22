/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:26:05 by uhand             #+#    #+#             */
/*   Updated: 2019/08/22 16:22:10 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "find_way.h"

static void	find_cur_room(t_link_breaker *br, t_find_way *find, \
	t_list_rooms *room)
{
	br->way = find->ways;
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
		br->croom = (t_list_rooms*)br->wroom->content;
		if (br->croom == room)
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
	t_list_rooms	*croom;

	wroom = wroom->left;
	while (wroom)
	{
		croom = (t_list_rooms*)wroom->content;
		if (croom->type == 0 && croom->act_lnks > 2)
			return (1);
		else if (croom->type == 1)
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
	if ((link->rm1 == croom && link->rm2 == prev_room) || \
		(link->rm2 == croom && link->rm1 == prev_room))
		return (1);
	return (0);
}

int			link_breaker(t_find_way *find, t_list_rooms *room)
{
	t_link_breaker	br;
	t_list_links	*link;
	t_list_rooms	*prev_room;
	t_list			*link_ptr;

	find_cur_room(&br, find, room);
	if (!check_connection(br.wroom))
		return (0);
	prev_room = (t_list_rooms*)br.wroom->left->content;
	link_ptr = br.croom->links;
	while (link_ptr)
	{
		link = (t_list_links*)link_ptr->content;
		if (check_link(link, br.croom, prev_room))
			break ;
		link_ptr = link_ptr->next;
	}
	if (!link_ptr)
	{
		ft_printf("Wrong links set!\n");
		ft_error();
	}
	link->status = 0;
	return (1);
}
