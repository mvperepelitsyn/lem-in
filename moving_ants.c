/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:07:51 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/18 20:59:44 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	status_changer(t_ant_farm *ant_farm)
{
	int i;

	while (ant_farm->ants[ant_farm->j].status == 0 && ant_farm->j < ant_farm->i)
	{
		if (ant_farm->ants[ant_farm->j].position->type == 2 && ant_farm->
				ants[ant_farm->j].finished == 0)
			ant_farm->ants[ant_farm->j].finished = 1;
		ant_farm->j++;
	}
	i = ant_farm->j;
	while (ant_farm->j < ant_farm->i)
	{
		if (ant_farm->ants[ant_farm->j].position->type == 2 && ant_farm->
				ants[ant_farm->j].finished == 0)
		{
			ant_farm->ants[ant_farm->j].finished = 1;
			ant_farm->ants[ant_farm->j].status = 0;
		}
		ant_farm->j++;
	}
	ant_farm->j = i;
}

static int	check_status(t_ant_farm *ant_farm)
{
	int i;

	i = 0;
	while (i < ant_farm->num)
	{
		if (ant_farm->ants[i].finished == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	help_move_ants_norm(t_intldta *intdta, t_find_way *find,
		t_ant_farm *ant_farm)
{
	t_list *ways;

	while (ant_farm->fin_ants <= intdta->num_ants && !check_status(ant_farm))
	{
		ant_farm->switcher = 0;
		ant_farm->ant_flow = 0;
		ways = find->answer->ways;
		ant_farm->j = 0;
		status_changer(ant_farm);
		move_what_is_moving(ant_farm);
		move_what_is_not_moving(find, ant_farm, ways);
		if (ant_farm->fin_ants <= intdta->num_ants && !check_status(ant_farm))
			ft_putchar('\n');
		if (intdta->v_flag && !check_status(ant_farm))
			ft_lstaddnext(&(find->ants_state), ant_farm->ants, sizeof(t_ants)
				* intdta->num_ants);
	}
}

void		move_ants(t_intldta *intdta, t_find_way *find)
{
	t_ant_farm	ant_farm;

	if ((long long)sizeof(t_ants) * (long long)intdta->num_ants > MAX_MEM)
		ft_malloc_error("You want to allocate more than MAX_MEM defined memory "
						"size for our ants!");
	if (!(ant_farm.ants = (t_ants *)ft_memalloc(sizeof(t_ants) * intdta->
			num_ants)))
		ft_malloc_error(NULL);
	ant_farm.num = intdta->num_ants;
	ant_farm.fin_ants = 0;
	ant_farm.full_steps = find->answer->full_steps;
	ant_farm.i = 0;
	if (intdta->v_flag)
		ant_color_init(ant_farm.ants, ant_farm.num);
	help_move_ants_norm(intdta, find, &ant_farm);
	free(ant_farm.ants);
	ant_farm.ants = NULL;
}
