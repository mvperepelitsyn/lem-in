//
// Created by Dwarven centurion Frost atronach on 2019-09-13.
//

#include "lem_in.h"

//static void free_t_list(t_list **lst)
//{
//	t_list *tmp;
//
//	while (*lst)
//	{
//		tmp = *lst;
//		free(tmp);
//		*lst = (*lst)->next;
//	}
//
//}
//
//static void free_t_list_rooms(t_list_rooms **rooms)
//{
//	t_list_rooms *tmp_room;
//
//	while (*rooms)
//	{
//		tmp_room = *rooms;
//		ft_strdel(&((*rooms)->name));
//		free_t_list(&((*rooms)->links));
//		*rooms = (*rooms)->next;
//		free(tmp_room);
//
//	}
//
//}
//
//void	free_indta(t_intldta **intldta)
//{
//	free_t_list_rooms(&((*intldta)->rooms));
//}