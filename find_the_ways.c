#include "lem_in.h"

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
 	//TODO: It's needed to make an inisialisation for crnt_set and prev_set
 	if (!((*fnd_wy)->ways = (t_way *)malloc(sizeof(t_way))))
 		ft_malloc_error();
	(*fnd_wy)->ways->rooms->content = ft_lstnew_addr((void *)indta->start_room, 0);
	(*fnd_wy)->ways->rooms->next = NULL;
	(*fnd_wy)->ways->len_way = 0;
	(*fnd_wy)->ways->num_way = 0;
	(*fnd_wy)->ways->next = NULL;
	(*fnd_wy)->start = indta->start_room;
	(*fnd_wy)->sets = NULL;
	(*fnd_wy)->crnt_set = NULL;
	(*fnd_wy)->way_nbr = 0;
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

//void	fill_the_way(t_find_way **fnd_wy, t_intldta *indta)
//{
// 	t_ways				*f_ways;
// 	t_list_rooms		*ptr;
//
// 	f_ways = (*fnd_wy)->crnt_set->ways;
// 	f_ways->way->rooms = (*fnd_wy)->shortest_way->rooms;
// 	while (1)
//	{
// 		while (f_ways->way->rooms->act_lnks != 0)
//
//	}
//
//
//}

//static void	fill_search(t_list_rooms **search)
//{
//	t_list_rooms	*tmp;
//	int 			act_lnks;
//
//	tmp = *search;
//	act_lnks = tmp->act_lnks;
//	while (act_lnks != 0)
//	{
//		tmp->next = (t_list_rooms *)malloc
//		act_lnks--;
//	}
//
//
//}
//
//static void wide_search(t_find_way **fnd_way, t_intldta *indta)
//{
//	t_list_rooms	*search;
//	t_list_rooms	*searched;
//
//	search = (t_list_rooms *)malloc(sizeof(t_list_rooms));
//	search = indta->start_room;
//	search->next = NULL;
//	while (ft_strequ(search->name, indta->end_room->name))
//	{
//		if (ft_strequ(search->name, indta->end_room->name))
//			break ;
//		else
//		{
//			while (search->act_lnks != 0)
//			{
//
//			}
//		}
//
//
//	}
//}

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*find;

 	init_set(&find, indta);
	while (!rec_finding(indta, find))
		continue ;
	if (CUR->full_steps == 0 || CUR->steps > PRE->steps)
		find->answer = PRE;
	else
		find->answer = CUR;
//	=> print answer
	if (indta->v_flag)
		visualizer(indta, find);
 	return (0);
}
