/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:00:44 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/15 17:12:14 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	help_test_links(t_list_rooms **current, t_list_links **links,
		short *check)
{
	while (*current)
	{
		if (ft_strequ((*links)->room1, (*current)->name))
		{
			(*links)->rm1 = *current;
			*check = *check + 1;
			break ;
		}
		if (!(*current = (*current)->next))
			break ;
	}
}

int			test_links(t_list_links **links, t_intldta **indta)
{
	t_list_rooms	*current;
	short			check;

	current = (*indta)->rooms;
	check = 0;
	help_test_links(&current, links, &check);
	current = (*indta)->rooms;
	while (current)
	{
		if (ft_strequ((*links)->room2, current->name))
		{
			(*links)->rm2 = current;
			check++;
			break ;
		}
		if (!(current = current->next))
			break ;
	}
	return ((check == 2) ? 1 : 0);
}

void		init_struct(t_intldta **indta)
{
	if (!((*indta) = (t_intldta *)ft_memalloc(sizeof(t_intldta))))
		ft_malloc_error(NULL);
	(*indta)->start_room = NULL;
	(*indta)->end_room = NULL;
	(*indta)->rooms = (t_list_rooms *)ft_memalloc(sizeof(t_list_rooms));
	(*indta)->links = (t_list_links *)ft_memalloc(sizeof(t_list_links));
	(*indta)->ri = -1;
	(*indta)->li = -1;
	(*indta)->links->next = NULL;
}

int			check_double_link(t_list_links *links, char **rms)
{
	char *rm1;
	char *rm2;

	rm1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
	rm2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
	if (ft_strequ(rm1, rm2))
	{
		ft_strdel(&rm1);
		ft_strdel(&rm2);
		return (1);
	}
	while (links)
	{
		if ((ft_strequ(rm1, links->room1) && ft_strequ(rm2, links->room2)) ||
		(ft_strequ(rm2, links->room1) && ft_strequ(rm1, links->room2)))
		{
			ft_strdel(&rm1);
			ft_strdel(&rm2);
			return (1);
		}
		links = links->next;
	}
	ft_strdel(&rm1);
	ft_strdel(&rm2);
	return (0);
}

void		free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
