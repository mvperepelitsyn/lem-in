/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:07:51 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/17 12:39:05 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	move_what_is_moving(t_ant_farm *ant_farm)
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
			}
			else
				ant_farm->ants[ant_farm->j].rooms = ant_farm->ants[ant_farm->j].
						rooms->right;
		}
		ant_farm->j++;
	}
}

static void	helper_to_move(t_find_way *find, t_ant_farm *ant_farm, t_list *ways)
{
	while (ant_farm->ant_flow < find->answer->ways_cnt && ant_farm->i <
			ant_farm->num)
	{
		while (ant_farm->switcher-- > 0)
			ways = ways->next;
		ant_farm->switcher = 1;
		while (ways && (*(t_way **)ways->content)->last_steps < 1)
			ways = ways->next;
		if (ways == NULL)
			break ;
		ant_farm->ants[ant_farm->i].status = 1;
		ant_farm->ants[ant_farm->i].way = *(t_way **)ways->content;
		(*(t_way **)ways->content)->last_steps--;
		ant_farm->ants[ant_farm->i].rooms = ant_farm->ants[ant_farm->i].way
				->rooms->right;
		ant_farm->ants[ant_farm->i].position = *(t_list_rooms **)
				(ant_farm->ants[ant_farm->i].rooms->content);
		ft_printf("L%d-%s ", ant_farm->i + 1, ant_farm->ants[ant_farm->i].
				position->name);
		ant_farm->ants[ant_farm->i].rooms = ant_farm->ants[ant_farm->i].
				rooms->right;
		ant_farm->ant_flow++;
		ant_farm->i++;
	}
}

static void	move_what_is_not_moving(t_find_way *find, t_ant_farm *ant_farm,
		t_list *ways)
{
	if (ant_farm->full_steps == 0)
		helper_to_move(find, ant_farm, ways);
	if (ant_farm->full_steps > 0)
	{
		while (ant_farm->full_steps > 0 && ant_farm->ant_flow < find->answer->
				ways_cnt && ant_farm->i < ant_farm->num)
		{
			while (ant_farm->switcher-- > 0)
				ways = ways->next;
			ant_farm->switcher = 1;
			ant_farm->ants[ant_farm->i].status = 1;
			ant_farm->ants[ant_farm->i].way = *(t_way **)ways->content;
			ant_farm->ants[ant_farm->i].rooms = ant_farm->ants[ant_farm->i].way
					->rooms->right;
			ant_farm->ants[ant_farm->i].position = *(t_list_rooms **)
					(ant_farm->ants[ant_farm->i].rooms->content);
			ft_printf("L%d-%s ", ant_farm->i + 1, ant_farm->ants[ant_farm->i].
					position->name);
			ant_farm->ants[ant_farm->i].rooms = ant_farm->ants[ant_farm->i].
					rooms->right;
			ant_farm->ant_flow++;
			ant_farm->i++;
		}
		ant_farm->full_steps--;
	}
}

static void	status_changer(t_ant_farm *ant_farm)
{
	while (ant_farm->ants[ant_farm->j].status == 0 && ant_farm->j < ant_farm->i)
	{
		if (ant_farm->ants[ant_farm->j].position->type == 2 && ant_farm->
		ants[ant_farm->j].finished == 0)
			ant_farm->ants[ant_farm->j].finished = 1;
		ant_farm->j++;
	}
}

void		move_ants(t_intldta *intdta, t_find_way *find)
{
	t_ant_farm	ant_farm;
	t_list		*ways;
	int			counter;
	void		*ptr;

	ant_farm.ants = (t_ants *)ft_memalloc(sizeof(t_ants) * intdta->num_ants);
	ant_farm.num = intdta->num_ants;
	ant_farm.fin_ants = 0;
	ant_farm.full_steps = find->answer->full_steps;
	counter = 0;
	ant_farm.i = 0;
	if (intdta->v_flag)
		ant_color_init(ant_farm.ants, ant_farm.num);
	while (ant_farm.fin_ants != intdta->num_ants)
	{
		ant_farm.switcher = 0;
		ant_farm.ant_flow = 0;
		ways = find->answer->ways;
		ant_farm.j = 0;
		status_changer(&ant_farm);
		move_what_is_moving(&ant_farm);
		move_what_is_not_moving(find, &ant_farm, ways);
		ft_putchar('\n');
		if (intdta->v_flag)
		{
			ptr = ft_memalloc((sizeof(t_ants) * intdta->num_ants));
			ft_memcpy(ptr, (void *)ant_farm.ants, sizeof(t_ants) * intdta->num_ants);
			ft_lstaddnext(&(find->ants_state), ptr, sizeof(t_ants) * intdta->num_ants);
		}
		counter++;
	}
	ft_printf("\nThe number of lines is %d\n", counter);
	free(ant_farm.ants);
	ant_farm.ants = NULL;
}
