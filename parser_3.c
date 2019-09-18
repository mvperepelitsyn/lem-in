/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:49:08 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/18 10:32:17 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_println(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

static	void	help_fill_list_links(t_list_links **lnks, char **rms)
{
	(*lnks)->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
	(*lnks)->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
	(*lnks)->next = NULL;
	(*lnks)->sttus = 1;
	(*lnks)->way_nbr = -1;
}

int				fill_list_links(t_list_links **lnks, char **rms, t_intldta **in)
{
	t_list_links	*current;

	current = (*lnks);
	if (++(*in)->li == 0)
	{
		help_fill_list_links(lnks, rms);
		if (!(test_links(lnks, in)))
			ft_error();
		(*in)->li++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		if (check_double_link(*lnks, rms))
			return (0);
		current->next = (t_list_links *)ft_memalloc(sizeof(t_list_links));
		help_fill_list_links(&(current->next), rms);
		if (!(test_links(&current->next, in)))
		{
			free_t_list_links(&current->next);
			return (1);
		}
	}
	return (0);
}

static void		type_assignment(t_list_rooms *room, t_intldta **indta)
{
	if (room->type != 0)
	{
		if (room->type == 1)
			(*indta)->start_room = room;
		else
			(*indta)->end_room = room;
	}
}

void			fill_list_rooms(char **rms, t_intldta **indta, short type)
{
	t_list_rooms *current;

	current = (*indta)->rooms;
	if (++(*indta)->ri == 0)
	{
		help_fill_list_rooms(rms, &((*indta)->rooms), type);
		type_assignment((*indta)->rooms, indta);
		(*indta)->rooms->next = NULL;
		(*indta)->ri++;
		test_double_room((*indta)->rooms->name, indta);
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_rooms *)ft_memalloc(sizeof(t_list_rooms));
		help_fill_list_rooms(rms, &(current->next), type);
		type_assignment(current->next, indta);
		current->next->next = NULL;
		test_double_room(current->next->name, indta);
	}
}
