/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/09/16 20:02:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_limits(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;

	ptr = indta->rooms->next;
	g->rooms_count = 0;
	while (ptr)
	{
		if (g->min_x > ptr->x_cord)
			g->min_x = ptr->x_cord;
		else if (g->max_x < ptr->x_cord)
			g->max_x = ptr->x_cord;
		if (g->min_y > ptr->y_cord)
			g->min_y = ptr->y_cord;
		else if (g->max_y < ptr->y_cord)
			g->max_y = ptr->y_cord;
		if(g->scale_rec <= 2)
		ptr = ptr->next;
		g->rooms_count++;
	}
	ptr = indta->rooms;
	while (ptr)
	{
		ptr->x_cord -= g->min_x;
		ptr->y_cord -= g->min_y;
		ptr = ptr->next;
	}
}

static void	coord_redef(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;
	int				count_x;
	int				x;
	int				y;

	count_x = sqrt((g->rooms_count * WIN_X) / WIN_Y);
	y = 0;
	ptr = indta->rooms;
	while (ptr)
	{
		x = 0;
		while (x < count_x && ptr)
		{
			ptr->x_cord = x;
			ptr->y_cord = y;
			x++;
			if (x < count_x)
				ptr = ptr->next;
		}
		y++;
		if (ptr)
			ptr = ptr->next;
	}
 }

static void	coord_init(t_intldta *indta, t_graph *g)
{
	g->scale_rec++;
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
	if (!g->scale && g->scale_rec < 2)
	{
		coord_redef(indta, g);
		coord_init(indta, g);
	}
}

static void	graph_init(t_graph *g, t_find_way *find, t_intldta *indta)
{
	g->v->win_x = g->delta_x + (R * 4);
	g->v->win_y = g->delta_y + (R * 4);
	g->mask->win_x = g->v->win_x;
	g->mask->win_y = g->v->win_y;
	g->graph->win_x = g->v->win_x;
	g->graph->win_y = g->v->win_y;
	g->clr[0] = R_CLR;
	g->clr[1] = S_CLR;
	g->clr[2] = F_CLR;
	g->set_ptr = find->sets;
	g->indta = indta;
	g->find = find;
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

void		set_map_transparent(t_vis_prms *v)
{
	int				alpha;
	size_t			img_len;
	size_t			i;
	unsigned int	*pixel;
	unsigned char	*byte;

	alpha  = (v->ndn == 0) ? 3 : 0;
	img_len = v->win_x * v->win_y;
	pixel = (unsigned int*)v->img_addr;
	i = 0;
	while (i < img_len)
	{
		byte = (unsigned char*)&pixel[i];
		pixel[i] = 0;
		byte[alpha] = 0xFF;
		i++;
	}
}

void		build_graph(t_intldta *indta, t_graph *g, t_find_way *find)
{
	t_way		**way;
	t_dllist	*room;
	t_list		*ptr;
	char		*str;

	draw_links(indta, g);
	draw_rooms(indta, g);
	mlx_clear_window (g->graph->mlx_ptr, g->graph->win_ptr);
	mlx_put_image_to_window(g->graph->mlx_ptr, g->graph->win_ptr, g->graph->img_ptr, 0, 0);
	ptr = g->set_ptr->ways;
	g->route_color = ROUTE_COLOR;
	set_map_transparent(g->mask);
	while (ptr)
	{
		way = ptr->content;
		room = (*way)->rooms;
		build_route(g, room);
		g->route_color += 1500000;
		transparent(&g->route_color, 0xAA, g->v);
		ptr = ptr->next;
	}
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->mask->img_ptr, 0, 0);
	str = NULL;
	ft_sprintf(&str, "ways: %d, steps: %d", g->set_ptr->ways_cnt, g->set_ptr->steps);
	mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, 5, 5, 0xFFFFFF, str);
	if (g->set_ptr == find->answer)
		mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, g->v->win_x - 80, 5, 0x00FF00, "Answer!");
	free(str);
}

/*static int	get_command(void *prm)
{
	t_vis_prms	*v;

	v = (t_vis_prms*)prm;
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->img_ptr, 0, 0);
	return (0);
}*/

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
	g.scale_rec = 0;
	coord_init(indta, &g);
	graph_init(&g, find, indta);
	window_init(&v, &mask, &graph);
	ft_printf("set steps: %d lala\n", g.set_ptr->steps);
	build_graph(indta, &g, find);
	//mlx_put_image_to_window(graph.mlx_ptr, graph.win_ptr, graph.img_ptr, 0, 0);
	mlx_hook(v.win_ptr, 2, 0, &deal_key, (void*)(&g));
	mlx_hook(v.win_ptr, 17, 0, &close_vis, (void*)(&g));
	//mlx_loop_hook(graph.mlx_ptr, &get_command, (void*)(&graph));
	mlx_loop(v.mlx_ptr);
}
