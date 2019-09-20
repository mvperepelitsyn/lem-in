/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 20:30:46 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		build_graph(t_intldta *indta, t_graph *g)
{
	t_way		**way;
	t_dllist	*room;
	t_list		*ptr;

	draw_links(indta, g);
	draw_rooms(indta, g);
	mlx_clear_window(g->graph->mlx_ptr, g->graph->win_ptr);
	mlx_put_image_to_window(g->graph->mlx_ptr, g->graph->win_ptr, \
		g->graph->img_ptr, 0, 0);
	ptr = g->set_ptr->ways;
	g->route_color = ROUTE_COLOR;
	set_map_transparent(g->mask);
	set_map_transparent(g->route);
	while (ptr)
	{
		way = ptr->content;
		room = (*way)->rooms;
		build_route(g, room);
		g->route_color += 1500000;
		mix_maps(g->mask, g->route, 0x88);
		ptr = ptr->next;
	}
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->route->img_ptr, \
		0, 0);
}

static void	draw_run_frame(t_graph *g)
{
	t_ants		*ants;
	int			ant;
	char		*str;

	put_images_to_window(g);
	ft_sprintf(&str, "step: %d / %d", g->step + 1, g->find->answer->steps);
	mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, 5, 5, 0xFFFFFF, str);
	free(str);
	if (g->info)
		sign_rooms(g->indta, g);
	if (g->step)
	{
		ants = (t_ants*)g->step_ptr->content;
		ant = 0;
		while (ant < g->indta->num_ants && g->frame < FRAMES_COUNT && g->info)
		{
			if (ants[ant].status || (ants[ant].position == g->indta->end_room \
				&& !ants[ant].finished))
				sign_ant_step(ants[ant].rooms, g, g->frame, ant);
			ant++;
		}
	}
}

static void	draw_static_frame(t_graph *g)
{
	char		*str;

	mlx_clear_window(g->v->mlx_ptr, g->v->win_ptr);
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, \
		g->graph->img_ptr, 0, 0);
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, \
		g->route->img_ptr, 0, 0);
	str = NULL;
	ft_sprintf(&str, "ways: %d, steps: %d", g->set_ptr->ways_cnt, \
	g->set_ptr->steps);
	mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, 5, 5, 0xFFFFFF, str);
	if (g->info)
		sign_rooms(g->indta, g);
	if (g->set_ptr == g->find->answer)
		mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, g->v->win_x - 80, 5, \
			0x00FF00, "Answer!");
	free(str);
}

static int	get_command(void *prm)
{
	t_graph		*g;

	g = (t_graph*)prm;
	if (g->run)
		vis_step(g, g->indta);
	else if (g->mode)
		draw_run_frame(g);
	else if (!g->mode)
		draw_static_frame(g);
	return (0);
}

void		visualizer(t_intldta *indta, t_find_way *find)
{
	t_graph		g;
	t_vis_prms	v;
	t_vis_prms	mask;
	t_vis_prms	graph;
	t_vis_prms	route;

	if (!indta->rooms)
		return ;
	ft_bzero(&g, sizeof(g));
	g.v = &v;
	g.mask = &mask;
	g.graph = &graph;
	g.route = &route;
	coord_init(indta, &g);
	graph_init(&g, find, indta);
	window_init(&v, &mask, &graph, &route);
	build_graph(indta, &g);
	set_map_transparent(g.v);
	mlx_hook(v.win_ptr, 2, 0, &deal_key, (void*)(&g));
	mlx_hook(v.win_ptr, 17, 0, &close_vis, (void*)(&g));
	mlx_loop_hook(graph.mlx_ptr, &get_command, (void*)(&g));
	mlx_loop(v.mlx_ptr);
}
