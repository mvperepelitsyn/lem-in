/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 15:15:44 by uhand             #+#    #+#             */
/*   Updated: 2019/08/16 11:52:55 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "finding.h"

static void	link_parsing(t_intldta **indta, char **things, char **rms)
{
    if (*((*indta)->start_room->name) == '\0' ||
    *((*indta)->end_room->name) == '\0')
        ft_error();
    rms = ft_strsplit(*things, '-');
    fill_list_links(&(*indta)->links, rms, indta);
    free_2d_array(rms);
}

static void start_stop_parsing(t_intldta **indta, char **things, char **rms, int fd)
{
	short	type;

	type = (ft_strequ("##start", *things)) ? 1 : 2;
    ft_strdel(things);
    get_next_line(fd, things);
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
        else if (ft_hm_wrd(*things, ' ') == 3)
        {
            rms = ft_strsplit(*things, ' ');
            fill_list_rooms(rms, indta, 0);
            free_2d_array(rms);
        }
        else if (ft_hm_wrd(*things, '-')  == 2)
            link_parsing(indta, things, rms);
        else if (!(*things && (things[0][0] == '#' && things[0][1] != '#')))
            ft_error();
        ft_strdel(things);
    }
}
