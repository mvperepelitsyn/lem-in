//
// Created by Dwarven centurion Frost atronach on 2019-09-09.
//

#include "lem_in.h"

void	move_what_is_moving(t_ant_farm *ant_farm)
{
	while (ant_farm->ants[ant_farm->j].status == 1 || ant_farm->j < ant_farm->i)
	{
		if (ant_farm->ants[ant_farm->j].status == 1)
		{
			ant_farm->ants[ant_farm->j].position = *(t_list_rooms **)
					(ant_farm->ants[ant_farm->j].rooms->content);
			ft_printf("L%d-%s ", ant_farm->j + 1, ant_farm->ants[ant_farm->j].
					position->name);
			if (ant_farm->ants[ant_farm->j].position->type == 2)
			{
				ant_farm->ants[ant_farm->j].status = 0;
				ant_farm->fin_ants++;
			} else
				ant_farm->ants[ant_farm->j].rooms = ant_farm->ants[ant_farm->j].
						rooms->right;
		}
		ant_farm->j++;
	}
}

void	move_ants(t_intldta *intdta, t_find_way *find)
{
	t_ant_farm	ant_farm;
	int 		tmp;
	t_list		*ways;

	ant_farm.ants = (t_ants *)ft_memalloc(sizeof(t_ants) * intdta->num_ants);
	ant_farm.num = intdta->num_ants;
	ant_farm.fin_ants = 0;
	ant_farm.full_steps = find->answer->full_steps;
	//TODO LIST: it the beginning we send ants full_steps times in every way
	// and then we decide where exactly we are going to send them
	ant_farm.i = 0;
	while (ant_farm.fin_ants != intdta->num_ants)
	{
		tmp = 0;
		ant_farm.ant_flow = 0;
		ways = find->answer->ways;
		ant_farm.j = 0;
		while (ant_farm.ants[ant_farm.j].status == 0 && ant_farm.j < ant_farm.i)
			ant_farm.j++;
		move_what_is_moving(&ant_farm);
		if (ant_farm.full_steps == 0)
		{
			while (ant_farm.ant_flow < find->answer->ways_cnt && ant_farm.i <
			        ant_farm.num)
			{
				while (tmp-- > 0)
					ways = ways->next;
				tmp = 1;
				while (ways && (*(t_way **)ways->content)->last_steps < 1)
					ways = ways->next;
				if (ways == NULL)
					break ;
				ant_farm.ants[ant_farm.i].status = 1;
				ant_farm.ants[ant_farm.i].way = *(t_way **)ways->content;
				(*(t_way **)ways->content)->last_steps--;
				ant_farm.ants[ant_farm.i].rooms = ant_farm.ants[ant_farm.i].way
						->rooms->right;
				ant_farm.ants[ant_farm.i].position = *(t_list_rooms **)
						(ant_farm.ants[ant_farm.i].rooms->content);
				ft_printf("L%d-%s ", ant_farm.i + 1, ant_farm.ants[ant_farm.i].
				position->name);
				ant_farm.ants[ant_farm.i].rooms = ant_farm.ants[ant_farm.i].
						rooms->right;
				ant_farm.ant_flow++;
				ant_farm.i++;
			}
		}
		if (ant_farm.full_steps > 0)
		{
			while (ant_farm.full_steps > 0 && ant_farm.ant_flow < find->answer->
			ways_cnt && ant_farm.i < ant_farm.num)
			{
				while (tmp-- > 0)
					ways = ways->next;
				tmp = 1;
				ant_farm.ants[ant_farm.i].status = 1;
				ant_farm.ants[ant_farm.i].way = *(t_way **) ways->content;
				ant_farm.ants[ant_farm.i].rooms = ant_farm.ants[ant_farm.i].way->rooms->right;
				ant_farm.ants[ant_farm.i].position = *(t_list_rooms **)
						(ant_farm.ants[ant_farm.i].rooms->content);
				ft_printf("L%d-%s ", ant_farm.i + 1, ant_farm.ants[ant_farm.i].
				position->name);
				ant_farm.ants[ant_farm.i].rooms = ant_farm.ants[ant_farm.i].
						rooms->right;
				ant_farm.ant_flow++;
				ant_farm.i++;
			}
			ant_farm.full_steps--;
		}
		ft_putchar('\n');
	}
	free(ant_farm.ants);
	ant_farm.ants = NULL;
}