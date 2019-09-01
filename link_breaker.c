/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 14:26:05 by uhand             #+#    #+#             */
/*   Updated: 2019/08/31 17:57:46 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	find_cur_room(t_link_breaker **br, t_find_way **find,
		t_list_rooms *room)
{
	t_link_breaker *tmp;
	tmp = *br;
	tmp->way = (*find)->ways;
	while (tmp->way)
	{
		if (tmp->way->num_way == room->way_nbr)
			break ;
		tmp->way = tmp->way->next;
	}
	if (!tmp->way)
	{
		ft_printf("Bad way number!\n");
		ft_error();
	}
	tmp->wroom = tmp->way->rooms;
	while (tmp->wroom)
	{
		tmp->croom = (t_list_rooms*)tmp->wroom->content;
		if (ft_strequ(tmp->croom->name, room->name))
			break ;
		tmp->wroom = tmp->wroom->right;
	}
	if (!tmp->wroom)
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

static void	break_links(t_link_breaker **br)
{
	t_link_breaker *tmp;
	t_intldta		*org;

	tmp = *br;
	while (tmp->wroom)
	{
		tmp->prev_room = (t_list_rooms*)tmp->wroom->left->content;
		tmp->link_ptr = tmp->croom->links;
		while (tmp->link_ptr)
		{
			tmp->link = (t_list_links*)tmp->link_ptr->content;
			if (check_link(tmp->link, tmp->croom, tmp->prev_room))
				break ;
			tmp->link_ptr = tmp->link_ptr->next;
		}
		if (!tmp->link_ptr)
		{
			ft_printf("Wrong links set!\n");
			ft_error();
		}
		tmp->link->status = 0;
		tmp->croom->act_lnks--;
		if (tmp->prev_room->act_lnks > 2)
		{
			tmp->prev_room->act_lnks--;
			break ;
		}
		tmp->prev_room->act_lnks--;
		tmp->wroom = tmp->wroom->left;
	}
}

int			link_breaker(t_find_way **find, t_list_rooms *room)
{
	t_link_breaker	*br;
	t_list_rooms	*test_room;

	br = (t_link_breaker *)ft_memalloc(sizeof(t_link_breaker));
	find_cur_room(&br, find, room);
	if (!check_connection(br->wroom))
		return (0);
	break_links(&br);
	test_room = (*find)->ways->rooms->right->content;
	br->wroom = br->way->rooms;
	while (br->wroom)
	{
		br->croom = (t_list_rooms *)br->wroom->content;
		br->croom->way_nbr = -1;
		br->wroom = br->wroom->right;
	}
	return (1);
}
