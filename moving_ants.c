//
// Created by Dwarven centurion Frost atronach on 2019-09-09.
//

#include "lem_in.h"

void	move_ants(t_intldta *intdta, t_find_way *find)
{
	t_ant_farm	ant_farm;
	int 		ant_flow;
	int 		i;
	int 		j;
	int 		tmp;
	t_list		*ways;
	int			counter;

	counter = 0;
	ant_farm.ants = (t_ants *)ft_memalloc(sizeof(t_ants) * intdta->num_ants);
	ant_farm.num = intdta->num_ants;
	ant_farm.fin_ants = 0;
	ant_farm.full_steps = find->answer->full_steps;
	//TODO LIST: it the beginning we send ants full_steps times in every way
	// and then we decide where exactly we are going to send them
	i = 0;
	while (ant_farm.fin_ants != intdta->num_ants)
	{
		tmp = 0;
		ant_flow = 0;
		ways = find->answer->ways;
		j = 0;
		while (ant_farm.ants[j].status == 0 && j < i)
			j++;
		while (ant_farm.ants[j].status == 1 || j < i)
		{
			if (ant_farm.ants[j].status == 1)
			{
				ant_farm.ants[j].position = *(t_list_rooms **) (ant_farm.ants
						[j].rooms->content);
				ft_printf("L%d-%s ", j + 1, ant_farm.ants[j].position->name);
				if (ant_farm.ants[j].position->type == 2)
				{
					ant_farm.ants[j].status = 0;
					ant_farm.fin_ants++;
				} else
					ant_farm.ants[j].rooms = ant_farm.ants[j].rooms->right;
			}
			j++;

		}
		if (ant_farm.full_steps == 0)
		{
			while (ant_flow < find->answer->ways_cnt && i < ant_farm.num)
			{
				while (tmp-- > 0)
					ways = ways->next;
				tmp = 1;
				while (ways && (*(t_way **)ways->content)->last_steps < 1)
					ways = ways->next;
				if (ways == NULL)
					break ;
				ant_farm.ants[i].status = 1;
				ant_farm.ants[i].way = *(t_way **)ways->content;
				(*(t_way **)ways->content)->last_steps--;
				ant_farm.ants[i].rooms = ant_farm.ants[i].way->rooms->right;
				ant_farm.ants[i].position = *(t_list_rooms **)(ant_farm.ants[i].
						rooms->content);
				ft_printf("L%d-%s ", i + 1, ant_farm.ants[i].position->name);
				ant_farm.ants[i].rooms = ant_farm.ants[i].rooms->right;
				ant_flow++;
				i++;
			}
		}
		if (ant_farm.full_steps > 0)
		{
			while (ant_farm.full_steps > 0 &&
				   ant_flow < find->answer->ways_cnt &&
				   i < ant_farm.num)
			{
				while (tmp-- > 0)
					ways = ways->next;
				tmp = 1;
				ant_farm.ants[i].status = 1;
				ant_farm.ants[i].way = *(t_way **) ways->content;
				ant_farm.ants[i].rooms = ant_farm.ants[i].way->rooms->right;
				ant_farm.ants[i].position = *(t_list_rooms **) (ant_farm.ants[i].
						rooms->content);
				ft_printf("L%d-%s ", i + 1, ant_farm.ants[i].position->name);
				ant_farm.ants[i].rooms = ant_farm.ants[i].rooms->right;
				ant_flow++;
				i++;
			}
			ant_farm.full_steps--;
		}
		counter++;
		ft_putchar('\n');
	}
	ft_printf("\nThe num of lines is %d\n", counter);
	free(ant_farm.ants);
	ant_farm.ants = NULL;
}


//void	move_ants(t_intldta *intdta, t_find_way *find)
//{
//	t_ant_farm	ant_farm;
//	int 		ant_flow;
//	int 		i;
//	int 		j;
//	int 		tmp;
//	t_list		*ways;
//	int			counter;
//
//	counter = 0;
//	ant_farm.ants = (t_ants *)ft_memalloc(sizeof(t_ants) * intdta->num_ants);
//	ant_farm.num = intdta->num_ants;
//	ant_farm.fin_ants = 0;
//	ant_farm.full_steps = find->answer->full_steps;
//	//TODO LIST: it the beginning we send ants full_steps times in every way
//	// and then we decide where exactly we are going to send them
//	i = 0;
//	while (ant_farm.fin_ants != intdta->num_ants)
//	{
//		tmp = 0;
//		ant_flow = 0;
//		ways = find->answer->ways;
//		j = 0;
//		while (ant_farm.ants[j].status == 0 && j < i)
//			j++;
//		while (ant_farm.ants[j].status == 1 || j < i)
//		{
//			if (ant_farm.ants[j].status == 1)
//			{
//				ant_farm.ants[j].position = *(t_list_rooms **) (ant_farm.ants
//				[j].rooms->content);
//				ft_printf("L%d-%s ", j + 1, ant_farm.ants[j].position->name);
//				if (ant_farm.ants[j].position->type == 2)
//				{
//					ant_farm.ants[j].status = 0;
//					ant_farm.fin_ants++;
//				} else
//					ant_farm.ants[j].rooms = ant_farm.ants[j].rooms->right;
//			}
//			j++;
//
//		}
//		while (ant_flow < find->answer->ways_cnt && i < ant_farm.num)
//		{
//			while (tmp-- > 0)
//				ways = ways->next;
//			tmp = 1;
//			while (ways && (*(t_way **)ways->content)->full_steps < 0)
//				ways = ways->next;
//			if (ways == NULL)
//				break ;
//			ant_farm.ants[i].status = 1;
//			ant_farm.ants[i].way = *(t_way **)ways->content;
//			(*(t_way **)ways->content)->full_steps--;
//			ant_farm.ants[i].rooms = ant_farm.ants[i].way->rooms->right;
//			ant_farm.ants[i].position = *(t_list_rooms **)(ant_farm.ants[i].
//					rooms->content);
//			ft_printf("L%d-%s ", i + 1, ant_farm.ants[i].position->name);
//			ant_farm.ants[i].rooms = ant_farm.ants[i].rooms->right;
//			ant_flow++;
//			i++;
//		}
//		counter++;
//		ft_putchar('\n');
//	}
//	ft_printf("\nThe num of lines is %d\n", counter);
//	free(ant_farm.ants);
//	ant_farm.ants = NULL;
//}