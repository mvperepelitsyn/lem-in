/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:12:56 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/18 17:51:49 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		init_ant(t_ants *ant)
{
	ant->status = 0;
	ant->finished = 0;
	ant->position = NULL;
	ant->rooms = NULL;
	ant->way = NULL;
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
		init_ant(&(ant_farm->ants[ant_farm->i]));
		ant_farm->ants[ant_farm->i].status = 1;
		ant_farm->ants[ant_farm->i].way = *(t_way **)ways->content;
		(*(t_way **)ways->content)->last_steps--;
		ant_farm->ants[ant_farm->i].rooms = ant_farm->ants[ant_farm->i].way
				->rooms->right;
		ant_farm->ants[ant_farm->i].position = *(t_list_rooms **)
				(ant_farm->ants[ant_farm->i].rooms->content);
		ft_printf("L%d-%s ", ant_farm->i + 1, ant_farm->ants[ant_farm->i].
				position->name);
		ant_farm->ant_flow++;
		ant_farm->i++;
	}
}

void		move_what_is_not_moving(t_find_way *find, t_ant_farm *ant_farm,
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
			init_ant(&(ant_farm->ants[ant_farm->i]));
			ant_farm->ants[ant_farm->i].status = 1;
			ant_farm->ants[ant_farm->i].way = *(t_way **)ways->content;
			ant_farm->ants[ant_farm->i].rooms = ant_farm->ants[ant_farm->i].way
					->rooms->right;
			ant_farm->ants[ant_farm->i].position = *(t_list_rooms **)
					(ant_farm->ants[ant_farm->i].rooms->content);
			ft_printf("L%d-%s ", ant_farm->i + 1, ant_farm->ants[ant_farm->i].
					position->name);
			ant_farm->ant_flow++;
			ant_farm->i++;
		}
		ant_farm->full_steps--;
	}
}

void		move_what_is_moving(t_ant_farm *ant_farm)
{
	while (ant_farm->ants[ant_farm->j].status == 1 || ant_farm->j < ant_farm->i)
	{
		if (ant_farm->ants[ant_farm->j].status == 1)
		{
			ant_farm->ants[ant_farm->j].rooms = ant_farm->ants[ant_farm->j].
					rooms->right;
			ant_farm->ants[ant_farm->j].position = *(t_list_rooms **)
					(ant_farm->ants[ant_farm->j].rooms->content);
			ft_printf("L%d-%s ", ant_farm->j + 1, ant_farm->ants[ant_farm->j].
					position->name);
			if (ant_farm->ants[ant_farm->j].position->type == 2)
			{
				ant_farm->ants[ant_farm->j].status = 0;
				ant_farm->fin_ants++;
			}
		}
		ant_farm->j++;
	}
}
