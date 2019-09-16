/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_breaker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 10:06:27 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/16 10:06:29 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	help_wide_breaker(t_list_links *link, t_list_rooms *room)
{
	link->sttus = 0;
	if (room == link->rm2)
		link->rm1->act_lnks--;
	else
		link->rm2->act_lnks--;
}

void		wide_breaker(t_list_links *link, t_list_rooms *room)
{
	t_wide_breaker	wr;

	help_wide_breaker(link, room);
	if (room->type == 1 || room->act_lnks != 2)
	{
		room->act_lnks--;
		return ;
	}
	room->act_lnks--;
	wr.link_ptr = room->links;
	while (wr.link_ptr)
	{
		wr.prev_link = *(t_list_links **)wr.link_ptr->content;
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
