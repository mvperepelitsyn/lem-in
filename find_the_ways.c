#include "find_way.h"

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
 	//TODO: It's needed to make an inisialisation for crnt_set and prev_set
 	if (!((*fnd_wy)->shortest_way = (t_way *)malloc(sizeof(t_way))))
 		ft_malloc_error();
	(*fnd_wy)->shortest_way->rooms->content = ft_lstnew_addr((void *)indta->start_room, 0);
	(*fnd_wy)->shortest_way->rooms->next = NULL;
	(*fnd_wy)->shortest_way->len_way = 0;
	(*fnd_wy)->shortest_way->num_way = 0;
	(*fnd_wy)->start = indta->start_room;
	 if (!((*fnd_wy)->crnt_set = (t_way_set *)malloc(sizeof(t_way_set))))
	 	ft_malloc_error();
	 (*fnd_wy)->crnt_set->steps_cnt = 0;
	 (*fnd_wy)->crnt_set->ways_cnt = 0;
}

//static void	copy_the_way(t_way *way)
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
 	t_ways				*f_ways;
 	t_list_rooms		*ptr;

 	f_ways = (*fnd_wy)->crnt_set->ways;
 	f_ways->way->rooms = (*fnd_wy)->shortest_way->rooms;
 	while (1)
	{
 		while (f_ways->way->rooms->act_lnks != 0)

	}


}

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*fnd_wy;

 	init_set(&fnd_wy, indta);
// 	exit (69);
 	fill_the_way(&fnd_wy, indta);
// 	print_the_way();
 	return (0);
}
