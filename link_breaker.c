/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:26:05 by uhand             #+#    #+#             */
/*   Updated: 2019/09/01 15:28:56 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_cur_room(t_link_breaker *br, t_find_way **find, t_list_rooms
*room)
{
	br->way = (*find)->ways;
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
		if (ft_strequ(br->croom->name, room->name))
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
	if ((ft_strequ(link->rm1->name,croom->name) && ft_strequ(link->rm2->name,
			prev_room->name)) || (ft_strequ(link->rm2->name, croom->name) &&
			ft_strequ(link->rm1->name, prev_room->name)))
		return (1);
	return (0);
}

static void	break_links(t_link_breaker *br)
{
	while (br->wroom)
	{
		br->prev_room = (t_list_rooms*)br->wroom->left->content;
		br->link_ptr = br->croom->links;
		while (br->link_ptr)
		{
			br->link = (t_list_links*)br->link_ptr->content;
			if (check_link(br->link, br->croom, br->prev_room))
				break ;
			br->link_ptr = br->link_ptr->next;
		}
		if (!br->link_ptr)
		{
			ft_printf("Wrong links set!\n");
			ft_error();
		}
		br->link->status = 0;
		br->croom->act_lnks--;
		if (br->prev_room->act_lnks > 2)
		{
			br->prev_room->act_lnks--;
			break ;
		}
		br->prev_room->act_lnks--;
		br->wroom = br->wroom->left;
	}
}

//TODO LIST: link_breaker changes status of the link, BUT does not change the state of rooms

//int			link_breaker(t_find_way **find, t_list_rooms *room)
//{
//	t_link_breaker	br;
//
//	find_cur_room(&br, find, room);
//	if (!check_connection(br.wroom))
//		return (0);
//	break_links(&br);
//	br.wroom = br.way->rooms;
//	while (br.wroom)
//	{
//		br.croom = (t_list_rooms *)br.wroom->content;
//		br.croom->way_nbr = -1;
//		br.croom->step_nbr = (br.croom->type != 1) ? -1 : 0;
//		br.wroom = br.wroom->right;
//	}
//	return (1);
//}

int			link_breaker(t_find_way **find, t_list_rooms *room)
{
	t_link_breaker	br;
	t_way			*tmp;
	t_list_rooms	*tmp2;

	tmp = (*find)->ways;
	find_cur_room(&br, find, room);
	if (!check_connection(br.wroom))
		return (0);
	break_links(&br);
	while (tmp->num_way != br.way->num_way)
		tmp = tmp->next;
	br.wroom = br.way->rooms;
	while (tmp->rooms)
	{
		tmp2 = tmp->rooms->content;
		tmp2->way_nbr = -1;
		tmp2->step_nbr = (tmp2->type != 1) ? -1 : 0;
		tmp->rooms = tmp->rooms->right;
	}
	return (1);
}
