/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:35:41 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/25 20:22:12 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_malloc_error(void)
{
	ft_putstr("Malloc didn't allocate the memory\n");
	exit (73);
}

void 	ft_error(void)
{
	ft_putstr("ERROR\n");
	exit(69);
}

void	ft_println(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

void	print_rooms(t_list_rooms *room)
{
	while (room)
	{
		ft_putstr(room->room->name);
		ft_putstr(" ");
		ft_putnbr(room->room->x_cord);
		ft_putstr(" ");
		ft_putnbr(room->room->y_cord);
		ft_putstr("\n");
		room = room->next;
	}
}

void	print_links(t_list_links *links)
{
	while (links)
	{
		ft_putstr(links->room1);
		ft_putstr("-");
		ft_putstr(links->room2);
		ft_putstr("\n");
		links = links->next;
	}
}

void	print_sides(t_room *room)
{
	ft_putstr(room->name);
	ft_putstr(" ");
	ft_putnbr(room->x_cord);
	ft_putstr(" ");
	ft_putnbr(room->y_cord);
	ft_putstr("\n");
}

void	ft_print_strcut(t_test *test)
{
	ft_putstr("The number of ants is ");
	ft_putnbr(test->num_ants);
	ft_putchar('\n');
	ft_putstr("Here goes the rooms:\n");
	ft_putstr("Start room: ");
	print_sides(test->start_room);
	ft_putstr("End room: ");
	print_sides(test->end_room);
	ft_putstr("Other rooms:\n");
	print_rooms(test->rooms);
	ft_putstr("Here comes the links: \n");
	print_links(test->links);
	ft_putstr("The end!");

}
