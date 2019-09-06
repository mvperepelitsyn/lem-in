/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/09/06 15:44:37 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_limits(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;

	ptr = indta->rooms->next;
	while (ptr)
	{
		//ptr->x_cord /= 10;
		//ptr->y_cord /= 10;
		if (g->min_x > ptr->x_cord)
			g->min_x = ptr->x_cord;
		else if (g->max_x < ptr->x_cord)
			g->max_x = ptr->x_cord;
		if (g->min_y > ptr->y_cord)
			g->min_y = ptr->y_cord;
		else if (g->max_y < ptr->y_cord)
			g->max_y = ptr->y_cord;
		ptr = ptr->next;
	}
	ptr = indta->rooms;
	while (ptr)
	{
		ptr->x_cord -= g->min_x;
		ptr->y_cord -= g->min_y;
		ptr = ptr->next;
	}
}

static void	graph_init(t_intldta *indta, t_graph *g)
{
	g->min_x = indta->rooms->x_cord;
	g->min_y = indta->rooms->y_cord;
	g->max_x = indta->rooms->x_cord;
	g->max_y = indta->rooms->y_cord;
	set_limits(indta, g);
	g->scale = SCALE;
	g->delta_x = (g->max_x - g->min_x) * g->scale;
	g->delta_y = (g->max_y - g->min_y) * g->scale;
	while ((g->delta_x + (R * 4)) > WIN_X || (g->delta_y + (R * 4)) > WIN_Y)
	{
		g->scale--;
		g->delta_x = (g->max_x - g->min_x) * g->scale;
		g->delta_y = (g->max_y - g->min_y) * g->scale;
	}
	 // if (!g->scale)
	 // 	coord_redef();
	g->v->win_x = g->delta_x + (R * 4);
	g->v->win_y = g->delta_y + (R * 4);
	g->mask->win_x = g->v->win_x;
	g->mask->win_y = g->v->win_y;
	g->graph->win_x = g->v->win_x;
	g->graph->win_y = g->v->win_y;
	g->clr[0] = R_CLR;
	g->clr[1] = S_CLR;
	g->clr[2] = F_CLR;
}

static void	window_init(t_vis_prms *v, t_vis_prms *mask, t_vis_prms *graph)
{
	v->mlx_ptr = mlx_init();
	mask->mlx_ptr = v->mlx_ptr;
	graph->mlx_ptr = v->mlx_ptr;

	v->win_ptr = mlx_new_window(v->mlx_ptr, v->win_x, v->win_y, "Lem_in");
	mask->win_ptr = v->win_ptr;
	graph->win_ptr = v->win_ptr;

	v->img_ptr = mlx_new_image(v->mlx_ptr, v->win_x, v->win_y);
	v->img_addr = mlx_get_data_addr(v->img_ptr, &v->bpp, &v->lsz, &v->ndn);

	mask->img_ptr = mlx_new_image(mask->mlx_ptr, v->win_x, v->win_y);
	mask->img_addr = mlx_get_data_addr(mask->img_ptr, &mask->bpp, \
		&mask->lsz, &mask->ndn);

	graph->img_ptr = mlx_new_image(graph->mlx_ptr, v->win_x, v->win_y);
	graph->img_addr = mlx_get_data_addr(graph->img_ptr, &graph->bpp, \
		&graph->lsz, &graph->ndn);
}

static void	build_graph(t_intldta *indta, t_graph *g, t_find_way *find)
{
	t_way		**way;
	t_dllist	*room;
	t_list		*ptr;

	draw_rooms(indta, g);
	draw_links(indta, g);
	// ptr = find->answer->ways;
	// way = ptr->content;
	// room = (*way)->rooms;
	// build_route(g, room);
}

static int	get_command(void *prm)
{
	t_vis_prms	*v;

	v = (t_vis_prms*)prm;
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->img_ptr, 0, 0);
	return (0);
}

void		visualizer(t_intldta *indta, t_find_way *find)
{
	t_graph		g;
	t_vis_prms	v;
	t_vis_prms	mask;
	t_vis_prms	graph;

	if (!indta->rooms)
		return ;
	g.v = &v;
	g.mask = &mask;
	g.graph = &graph;
	graph_init(indta, &g);
	window_init(&v, &mask, &graph);
	build_graph(indta, &g, find);
	mlx_put_image_to_window(graph.mlx_ptr, graph.win_ptr, graph.img_ptr, 0, 0);
	mlx_hook(v.win_ptr, 2, 0, &deal_key, (void*)(&v));
	mlx_hook(v.win_ptr, 17, 0, &close_vis, (void*)(&v));
	mlx_loop_hook(graph.mlx_ptr, &get_command, (void*)(&graph));
	mlx_loop(v.mlx_ptr);
}
