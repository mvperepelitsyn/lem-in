/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:04:14 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/28 16:11:39 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <fcntl.h> //DO NOT FORGET TO REMOVE IT!!!

void	fill_list_rooms(char **rms, t_test **test)
{
	t_list_rooms *current;

	current = (*test)->rooms;
	if (++(*test)->rooms->i == 0)
	{
		(*test)->rooms->room = (t_room *)malloc(sizeof(t_room));
		(*test)->rooms->room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		test_name((*test)->rooms->room->name);
		(*test)->rooms->room->x_cord = ft_latoi(rms[1]);
		(*test)->rooms->room->y_cord = ft_latoi(rms[2]);
		test_coord((*test)->rooms->room->x_cord, (*test)->rooms->room->y_cord);
		(*test)->rooms->next = NULL;
		(*test)->rooms->i++;
		test_double_room((*test)->rooms->room->name, test);
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
		current->next->room = (t_room *)malloc(sizeof(t_room));
		current->next->room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		test_name(current->next->room->name);
		current->next->room->x_cord = ft_latoi(rms[1]);
		current->next->room->y_cord = ft_latoi(rms[2]);
		test_coord(current->next->room->x_cord, current->next->room->y_cord);
		current->next->next = NULL;
		test_double_room(current->next->room->name, test);
	}
}

void	fill_list_links(t_list_links **links, char **rms, t_test *test)
{
	t_list_links	*current;

	current = (*links);
	if (++(*links)->i == 0)
	{
		(*links)->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*links)->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		if (!(test_links((*links)->room1, (*links)->room2, test)))
			ft_error();
		(*links)->next = NULL;
		(*links)->i++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		if (check_double_link(*links, rms))
			return ;
		current->next = (t_list_links *)malloc(sizeof(t_list_links));
		current->next->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		current->next->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		if (!(test_links(current->next->room1, current->next->room2, test)))
			ft_error();
		current->next->next = NULL;
	}
}

void	parce_ant_farm(t_test **test) //when we force it to read
{
	char	*things;
	char	**rms;
	int		fd;

	if ((fd = open(NAME, O_RDONLY)) < 0)
		fd = 0;
	get_next_line(fd, &things);
	(things == NULL) ? ft_error() : ft_println(things);
	(*test)->num_ants = ft_latoi(things);
	if ((*test)->num_ants <= 0 || (*test)->num_ants > 2147483647)
		ft_error();
	ft_strdel(&things);
	(*test)->rooms = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	(*test)->links = (t_list_links *)malloc(sizeof(t_list_links));
	(*test)->rooms->i = -1;
	(*test)->links->i = -1;
	(*test)->links->next = NULL;
	while (get_next_line(fd, &things))
	{
		ft_println(things);
		if (ft_strequ("##start", things))
		{
			ft_strdel(&things);
			get_next_line(fd, &things);
			ft_println(things);
			rms = ft_strsplit(things, ' ');
			if (ft_hm_wrd(things, ' ') != 3)
				ft_error();
			(*((*test)->start_room->name) == '\0') ? ft_strdel(&(*test)->start_room->name) :
			ft_error();
//			test->start_room = (t_room *)malloc(sizeof(t_room));
			(*test)->start_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test_name((*test)->start_room->name);
			(*test)->start_room->x_cord = ft_latoi(rms[1]);
			(*test)->start_room->y_cord = ft_latoi(rms[2]);
			test_coord((*test)->start_room->x_cord, (*test)->start_room->y_cord);
			free_2d_array(rms);
		}
		else if (ft_strequ("##end", things))
		{
			ft_strdel(&things);
			get_next_line(fd, &things);
			ft_println(things);
			rms = ft_strsplit(things, ' ');
			if (ft_hm_wrd(things, ' ') != 3)
				ft_error();
			(*((*test)->end_room->name) == '\0') ? ft_strdel(&(*test)->end_room->name) :
			ft_error();
//			test->end_room = (t_room *)malloc(sizeof(t_room));
			(*test)->end_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test_name((*test)->end_room->name);
			(*test)->end_room->x_cord = ft_latoi(rms[1]);
			(*test)->end_room->y_cord = ft_latoi(rms[2]);
			test_coord((*test)->end_room->x_cord, (*test)->end_room->y_cord);
			free_2d_array(rms);
		}
		else if (ft_hm_wrd(things, ' ') == 3)
		{
			rms = ft_strsplit(things, ' ');
			fill_list_rooms(rms, test);
			free_2d_array(rms);
		}
		else if (ft_hm_wrd(things, '-')  == 2)
		{
			if (*((*test)->start_room->name) == '\0' || *((*test)->end_room->name) == '\0')
				ft_error();
			rms = ft_strsplit(things, '-');
			fill_list_links(&(*test)->links, rms, (*test));
			free_2d_array(rms);
		}
		ft_strdel(&things);
	}
	if ((*test)->links->i == -1)
		ft_error();
}

//TODO: make a validation
//1)The number of ants (check)
//2)Exception in names of the rooms (cant start with the character L nor the character #) (check)
//3)The size of the coordinates (int) (check)
//4)Valid rooms in links (check, but not really)
//5)Make it skeep the repetitive links


int		main()
{
	t_test	*test;

	if (!(test = (t_test *)malloc(sizeof(t_test))))
		ft_malloc_error();
	init_struct(&test);
	parce_ant_farm(&test);
	ft_print_strcut(&test);
	exit (0);
}