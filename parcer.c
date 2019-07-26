/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:04:14 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/26 16:41:16 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcer.h"

#include <fcntl.h> //DO NOT FORGET TO REMOVE IT!!!

void	fill_list_rooms(t_list_rooms **rooms, char **rms)
{
	t_list_rooms *current;

	current = (*rooms);
	if ((*rooms)->i == 0)
	{
		(*rooms)->room = (t_room *)malloc(sizeof(t_room));
		(*rooms)->room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*rooms)->room->x_cord = ft_latoi(rms[1]);
		(*rooms)->room->y_cord = ft_latoi(rms[2]);
		test_coord((*rooms)->room->x_cord, (*rooms)->room->y_cord);
		(*rooms)->next = NULL;
		(*rooms)->i++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
		current->next->room = (t_room *)malloc(sizeof(t_room));
		current->next->room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		current->next->room->x_cord = ft_latoi(rms[1]);
		current->next->room->y_cord = ft_latoi(rms[2]);
		test_coord(current->next->room->x_cord, current->next->room->y_cord);
		current->next->next = NULL;
	}
}

void	fill_list_links(t_list_links **links, char **rms)
{
	t_list_links	*current;

	current = (*links);
	if ((*links)->i == 0)
	{
		(*links)->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*links)->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		(*links)->next = NULL;
		(*links)->i++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_links *)malloc(sizeof(t_list_links));
		current->next->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		current->next->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		current->next->next = NULL;
	}
}

void	parce_ant_farm(t_test *test) //when we force it to read
{
	char	*things;
	char	**rms;
	int		fd;

	if ((fd = open(NAME, O_RDONLY)) < 0)
		fd = 0;
	get_next_line(fd, &things);
	ft_println(things);
	test->num_ants = ft_latoi(things);
	if (test->num_ants <= 0 || test->num_ants > 2147483647)
		ft_error();
	ft_strdel(&things);
	test->rooms = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	test->links = (t_list_links *)malloc(sizeof(t_list_links));
	test->rooms->i = 0;
	test->links->i = 0;
	test->links->next = NULL;
	while (get_next_line(fd, &things))
	{
		ft_println(things);
		if (ft_strequ("##start", things))
		{
			ft_strdel(&things);
			get_next_line(fd, &things);
			ft_println(things);
			rms = ft_strsplit(things, ' ');
			test->start_room = (t_room *)malloc(sizeof(t_room));
			test->start_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test->start_room->x_cord = ft_latoi(rms[1]);
			test->start_room->y_cord = ft_latoi(rms[2]);
			test_coord(test->start_room->x_cord, test->start_room->y_cord);
		}
		else if (ft_strequ("##end", things))
		{
			ft_strdel(&things);
			get_next_line(fd, &things);
			ft_println(things);
			rms = ft_strsplit(things, ' ');
			test->end_room = (t_room *)malloc(sizeof(t_room));
			test->end_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test->end_room->x_cord = ft_latoi(rms[1]);
			test->end_room->y_cord = ft_latoi(rms[2]);
			test_coord(test->end_room->x_cord, test->end_room->y_cord);
		}
		else if (ft_hm_wrd(things, ' ') == 3)
		{
			rms = ft_strsplit(things, ' ');
			fill_list_rooms(&test->rooms, rms);
		}
		else if (ft_hm_wrd(things, '-'))
		{
			rms = ft_strsplit(things, '-');
			fill_list_links(&test->links, rms);
		}
		ft_strdel(&things);
	}
}

//TODO: make a validation
//1)The number of ants (check)
//2)Exception in names of the rooms (cant start with the character L nor the character #)
//3)The size of the coordinates (int) (check)
//4)Valid rooms in links
//5)


int		main()
{
	t_test	*test;

	ft_putstr("Here what in file:\n");
	if (!(test = (t_test *)malloc(sizeof(t_test))))
		ft_malloc_error();
	parce_ant_farm(test);
	ft_putstr("\nHere what we've read:\n");
	ft_print_strcut(test);
	exit (0);
}