#include "find_way.h"

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
 	//TODO: It's needed to make an inisialisation for crnt_set and prev_set
 	if (!((*fnd_wy)->shortest_way = (t_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
	 (*fnd_wy)->shortest_way->len_way = 0;
	 (*fnd_wy)->shortest_way->num_way = 0;
	 (*fnd_wy)->start = indta->start_room;
	 if (!((*fnd_wy)->crnt_set = (t_way_set * )malloc(sizeof(t_way_set))))
	 	ft_malloc_error();
	 (*fnd_wy)->crnt_set->steps_cnt = 0;
	 (*fnd_wy)->crnt_set->ways_cnt = 0;
}

//static void	print_the_way(t_way *way)
//{
// 	ft_putstr("This is the way:\n");
// 	ft_putstr(way->room);
// 	way = way->next;
// 	while (way)
// 	{
// 		ft_putstr("->");
// 		ft_putstr(way->room);
// 		way = way->next;
// 	}
//}

void	fill_the_way(t_find_way **fnd_wy, t_intldta *indta)
{
 	t_find_way			*new_fd_wy;
 	t_list_links		*lnks;

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
}

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*fnd_wy;

 	init_set(&fnd_wy, indta);
 	exit (69);
 	fill_the_way(&fnd_wy, indta);
// 	print_the_way();
 	return (0);
}
