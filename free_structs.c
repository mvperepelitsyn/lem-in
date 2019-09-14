//
// Created by Dwarven centurion Frost atronach on 2019-09-13.
//

#include "lem_in.h"

static void free_t_list_rooms(t_list_rooms **rooms)
{
	t_list_rooms *tmp_room;

	while (*rooms)
	{
		ft_strdel(&((*rooms)->name));
		ft_lstdel(&((*rooms)->links), &ft_lstfree);
		tmp_room = (*rooms)->next;
		(*rooms)->next = NULL;
		free(*rooms);
		*rooms = NULL;
		*rooms = tmp_room;
	}
}

static void	free_t_list_links(t_list_links **links)
{
	t_list_links *tmp_lnk;

	while (*links)
	{
		ft_strdel(&((*links)->room1));
		ft_strdel(&((*links)->room2));
		(*links)->rm1 = NULL;
		(*links)->rm2 = NULL;
		tmp_lnk = (*links)->next;
		free(*links);
		(*links)->next = NULL;
		*links = NULL;
		*links = tmp_lnk;
	}
}

void	free_indta(t_intldta **intldta)
{
	free_t_list_rooms(&((*intldta)->rooms));
	free_t_list_links(&((*intldta)->links));
	(*intldta)->start_room->status = (*intldta)->end_room->num_lnks;
	free(*intldta);
	*intldta = NULL;
}