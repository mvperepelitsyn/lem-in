//
// Created by Dwarven centurion Frost atronach on 2019-09-09.
//

#include "lem_in.h"

//void	move_ants(t_intldta *intdta, t_find_way *find)
//{
//	t_ants	*ants;
//	int 	num;
//	int 	ant_flow;
//	int 	i;
//	int 	tmp;
//	t_list	*ways;
//
//	ants = (t_ants *)ft_memalloc(sizeof(t_ants) * intdta->num_ants);
//	num = intdta->num_ants;
//	i = 0;
//	while (num)
//	{
//		ant_flow = 0;
//		ways = find->answer->ways;
//		while (ant_flow < find->answer->ways_cnt)
//		{
//			tmp = ant_flow;
//			ants[i].status = 1;
//			while (tmp > 0)
//			{
//				tmp--;
//				ways = ways->next;
//			}
//			ants[i].way = ways->content;
//			ants[i].position = (t_list_rooms *)(ants[i].way->rooms);
//			ant_flow++;
//			i++;
//		}
//
//		num--;
//	}
//}