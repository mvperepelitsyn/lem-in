#include "finding.h"

// static void	init_the_way(t_flow **flow)
// {
// 	if (!((*flow) = (t_flow *)malloc(sizeof(t_flow))))
// 		ft_malloc_error();
// 	(*flow)->length_way = 0;
// 	(*flow)->way = NULL;
// 	(*flow)->next = NULL;
// }
//
// void	print_the_way(t_way *way)
// {
// 	ft_putstr("This is the way:\n");
// 	ft_putstr(way->room);
// 	way = way->next;
// 	while (way)
// 	{
// 		ft_putstr("->");
// 		ft_putstr(way->room);
// 		way = way->next;
// 	}
// }
//
// void	fill_the_way(t_flow **flow, t_intldta *indta)
// {
// 	t_flow			*crnt_flw;
// 	t_list_links	*lnks;
//
// 	crnt_flw = (*flow);
// 	while (!ft_strequ(wy->room, indta->end_room->name))
// 	{
// 		lnks = indta->links;
// 		if (wy->prev != NULL)
// 			while (!((ft_strequ(wy->room, lnks->room1) && !ft_strequ(wy->prev->room,
// 				lnks->room2)) || (ft_strequ(wy->room, lnks->room2) &&
// 				!ft_strequ(wy->prev->room, lnks->room1))))
// 				lnks = lnks->next;
// 		else
// 			while (!(ft_strequ(wy->room, lnks->room1) || (ft_strequ(wy->room,
// 					lnks->room2))))
// 				lnks = lnks->next;
// 		if (ft_strequ(wy->room, lnks->room1))
// 		{
// 			wy->next = (t_way *)malloc(sizeof(t_way));
// 			wy->next->room = ft_strsub(lnks->room2, 0, ft_strlen(lnks->room2));
// 		}
// 		else
// 		{
// 			wy->next = (t_way *)malloc(sizeof(t_way));
// 			wy->next->room = ft_strsub(lnks->room1, 0, ft_strlen(lnks->room1));
// 		}
// 		wy->next->prev = wy;
// 		wy->next->next = NULL;
// 		wy = wy->next;
// 	}
// }
//
// int 	find_the_way(t_intldta *indta)
// {
// 	t_flow			*flow;
//
// 	init_the_way(&flow);
// 	fill_the_way(&flow, indta);
// 	print_the_way(flow);
// 	return (0);
// }
