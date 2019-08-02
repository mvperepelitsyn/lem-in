/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/08/02 16:01:07 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	set_limits(t_intldta *indta, t_graph *g)
{
	ptr = indta->rooms->next;
	while (ptr)
	{
		if (g->min_x > (int)ptr->x_cord)
			g->min_x = (int)ptr->x_cord;
		else if (g->max_x < (int)ptr->x_cord)
			g->max_x = (int)ptr->x_cord;
		if (g->min_y > (int)ptr->y_cord)
			g->min_y = (int)ptr->y_cord;
		else if (g->max_y < (int)ptr->y_cord)
			g->max_y = (int)ptr->y_cord;
		ptr = ptr->next;
	}
}

static void	graph_init(t_intldta *indta, t_graph *g)
{
	t_room	*ptr;

	g->min_x = (int)indta->rooms->x_cord;
	g->min_y = (int)indta->rooms->y_cord;
	g->max_x = (int)indta->rooms->x_cord;
	g->max_y = (int)indta->rooms->y_cord;
	set_limits(indta, g);
	g->scale = SCALE;
	g->delta_x = (g->max_x - g->min_x) * g->scale;
	g->delta_y = (g->max_y - g->min_y) * g->scale;
	while ((g->delta_x + (R * 2)) > WIN_X || (g->delta_y + (R * 2)) > WIN_Y)
	{
		g->scale--;
		g->delta_x = (g->max_x - g->min_x) * g->scale;
		g->delta_y = (g->max_y - g->min_y) * g->scale;
	}
}

static void	build_graph(t_intldta *indta)
{
	//
}

void		visualizer(t_intldta *indta)
{
	t_graph	g;

	if (!indta->rooms)
		return ;
	graph_init(indta, &g);
	build_graph(indta);
}