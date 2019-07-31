/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_the_ways.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:45:02 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/31 16:35:11 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "finding.h"

void	init_the_way(t_way **way, t_intldta *indta)
{
	if (!((*way) = (t_way *)malloc(sizeof(t_way))))
		ft_malloc_error();
	(*way)->room = ft_strsub(indta->start_room->name, 0, ft_strlen(indta->
	start_room->name));
	(*way)->next = NULL;
	(*way)->prev = NULL;
}

void	print_the_way(t_way *way)
{
	ft_putstr("This is the way:\n");
	ft_putstr(way->room);
	way = way->next;
	while (way)
	{
		ft_putstr("->");
		ft_putstr(way->room);
		way = way->next;
	}
}

void	fill_the_way(t_way **way, t_intldta *indta)
{
	t_way			*wy;
	t_list_links	*lnks;

	wy = (*way);
	while (!ft_strequ(wy->room, indta->end_room->name))
	{
		lnks = indta->links;
		if (wy->prev != NULL)
			while (!((ft_strequ(wy->room, lnks->room1) && !ft_strequ(wy->prev->room,
				lnks->room2)) || (ft_strequ(wy->room, lnks->room2) &&
				!ft_strequ(wy->prev->room, lnks->room1))))
				lnks = lnks->next;
		else
			while (!(ft_strequ(wy->room, lnks->room1) || (ft_strequ(wy->room,
					lnks->room2))))
				lnks = lnks->next;
		if (ft_strequ(wy->room, lnks->room1))
		{
			wy->next = (t_way *)malloc(sizeof(t_way));
			wy->next->room = ft_strsub(lnks->room2, 0, ft_strlen(lnks->room2));
		}
		else
		{
			wy->next = (t_way *)malloc(sizeof(t_way));
			wy->next->room = ft_strsub(lnks->room1, 0, ft_strlen(lnks->room1));
		}
		wy->next->prev = wy;
		wy->next->next = NULL;
		wy = wy->next;
	}
}

int 	find_the_way(t_intldta *indta)
{
	t_way			*way;
	t_list_links	*lnks;

	init_the_way(&way, indta);
	fill_the_way(&way, indta);
	print_the_way(way);
	return (0);
}