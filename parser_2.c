/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:15:44 by uhand             #+#    #+#             */
/*   Updated: 2019/09/15 15:50:32 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_println(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

static int link_parsing(t_intldta **indta, char **things, char **rms)
{
	if ((*indta)->start_room == NULL || (*indta)->end_room == NULL)
		ft_error();
	rms = ft_strsplit(*things, '-');
	if (fill_list_links(&(*indta)->links, rms, indta))
	{
		free_2d_array(rms);
		ft_strdel(things);
		return (1);
	}
	free_2d_array(rms);
	return (0);
}

static void	help_start_stop(char **things, int fd)
{
	ft_println(*things);
	if (things[0][1] == '#')
	{
		ft_strdel(things);
		ft_error();
	}
	ft_println(*things);
	ft_strdel(things);
	get_next_line(fd, things);
}

static void	start_stop_parsing(t_intldta **indta, char **things, char **rms,
		int fd)
{
	short	type;

	type = (ft_strequ("##start", *things)) ? 1 : 2;
	if ((ft_strequ("##start", *things) && (*indta)->start_room != NULL) ||
			(ft_strequ("##end", *things) && (*indta)->end_room != NULL))
	{
		ft_strdel(things);
		ft_error();
	}
	ft_strdel(things);
	get_next_line(fd, things);
	while (**things == '#')
		help_start_stop(things, fd);
	ft_println(*things);
	rms = ft_strsplit(*things, ' ');
	if (ft_hm_wrd(*things, ' ') != 3)
		ft_error();
	fill_list_rooms(rms, indta, type);
	free_2d_array(rms);
}

void		graph_parser(t_intldta **indta, char **things, char **rms, int fd)
{
	while (get_next_line(fd, things))
	{
		ft_println(*things);
		if (ft_strequ("##start", *things))
			start_stop_parsing(indta, things, rms, fd);
		else if (ft_strequ("##end", *things))
			start_stop_parsing(indta, things, rms, fd);
		else if (*things[0] == '#')
		{
			ft_strdel(things);
			continue ;
		}
		else if (ft_hm_wrd(*things, ' ') == 3)
		{
			rms = ft_strsplit(*things, ' ');
			fill_list_rooms(rms, indta, 0);
			free_2d_array(rms);
		}
		else if (ft_hm_wrd(*things, '-') == 2)
		{
			if (link_parsing(indta, things, rms))
				return;
		}
		else if (!(*things && (things[0][0] == '#' && things[0][1] != '#')))
			ft_error();
		ft_strdel(things);
	}
}
