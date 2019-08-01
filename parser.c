/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:04:14 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/08/01 12:50:29 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "finding.h"

#include <fcntl.h> //DO NOT FORGET TO REMOVE IT!!!

void	fill_list_rooms(char **rms, t_intldta **indta)
{
	t_list_rooms *current;

	current = (*indta)->rooms;
	if (++(*indta)->rooms->i == 0)
	{
		(*indta)->rooms->room = (t_room *)malloc(sizeof(t_room));
		help_fill_list_rooms(rms, &((*indta)->rooms->room));
		(*indta)->rooms->next = NULL;
		(*indta)->rooms->i++;
		test_double_room((*indta)->rooms->room->name, indta);
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
		current->next->room = (t_room *)malloc(sizeof(t_room));
		help_fill_list_rooms(rms, &(current->next->room));
		current->next->next = NULL;
		test_double_room(current->next->room->name, indta);
	}
}

void	fill_list_links(t_list_links **links, char **rms, t_intldta *indta)
{
	t_list_links	*current;

	current = (*links);
	if (++(*links)->i == 0)
	{
		(*links)->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*links)->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		if (!(test_links((*links)->room1, (*links)->room2, indta)))
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
		if (!(test_links(current->next->room1, current->next->room2, indta)))
			ft_error();
		current->next->next = NULL;
	}
}

void	parce_ant_farm(t_intldta **indta) //when we force it to read
{
	char	*things;
	char	**rms;
	int		fd;

	if ((fd = open(NAME, O_RDONLY)) < 0)
		fd = 0;
	get_next_line(fd, &things);
	(things == NULL) ? ft_error() : ft_println(things);
	while (things && (things[0] == '#' && things[1] != '#'))
    {
        ft_strdel(&things);
        things = NULL;
        get_next_line(fd, &things);
        if (things)
            ft_println(things);
    }
	(*indta)->num_ants = ft_latoi(things);
	if ((*indta)->num_ants <= 0 || (*indta)->num_ants > 2147483647)
		ft_error();
	ft_strdel(&things);
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
			(*((*indta)->start_room->name) == '\0') ? ft_strdel(&(*indta)->start_room->name) :
			ft_error();
			(*indta)->start_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test_name((*indta)->start_room->name);
			(*indta)->start_room->x_cord = ft_latoi(rms[1]);
			(*indta)->start_room->y_cord = ft_latoi(rms[2]);
			test_coord((*indta)->start_room->x_cord, (*indta)->start_room->y_cord);
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
			(*((*indta)->end_room->name) == '\0') ? ft_strdel(&(*indta)->end_room->name) :
			ft_error();
			(*indta)->end_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test_name((*indta)->end_room->name);
			(*indta)->end_room->x_cord = ft_latoi(rms[1]);
			(*indta)->end_room->y_cord = ft_latoi(rms[2]);
			test_coord((*indta)->end_room->x_cord, (*indta)->end_room->y_cord);
			free_2d_array(rms);
		}
		else if (ft_hm_wrd(things, ' ') == 3)
		{
			rms = ft_strsplit(things, ' ');
			fill_list_rooms(rms, indta);
			free_2d_array(rms);
		}
		else if (ft_hm_wrd(things, '-')  == 2)
		{
			if (*((*indta)->start_room->name) == '\0' || *((*indta)->end_room->name) == '\0')
				ft_error();
			rms = ft_strsplit(things, '-');
			fill_list_links(&(*indta)->links, rms, (*indta));
			free_2d_array(rms);
		}
		else if (!(things && (things[0] == '#' && things[1] != '#')))
            ft_error();
		ft_strdel(&things);
	}
	if ((*indta)->links->i == -1)
		ft_error();

}

int		main()
{
	t_intldta	*indta;

	init_struct(&indta);
	parce_ant_farm(&indta);
	ft_print_strcut(&indta);
	ft_putchar('\n');
	find_the_way(indta);
	exit (0);
}