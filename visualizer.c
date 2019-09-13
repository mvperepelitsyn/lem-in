/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/09/13 19:19:39 by uhand            ###   ########.fr       */
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
		g->rooms_count++;
		if(g->scale_rec <= 2)
			ft_printf(" : %d %d\n", ptr->x_cord, ptr->y_cord);
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

	// block = (float)g->rooms_count / (BLOCK_X * BLOCK_Y);
	// block = (block > (int)block) ? block++ : block;
	count_x = sqrt((g->rooms_count * BLOCK_X) / BLOCK_Y);
	count_x++;
	y = 0;
	ptr = indta->rooms;
	while (ptr)
	{
		x = 0;
		while (x < count_x && ptr)
		{
			ft_printf("%d %d", ptr->x_cord, ptr->y_cord);
			ptr->x_cord = x;
			ptr->y_cord = y;
			ft_printf(" : %d %d\n", ptr->x_cord, ptr->y_cord);
			ptr = ptr->next;
			x++;
		}
		y++;
		if (ptr)
			ptr = ptr->next;
	}
 }

static void	graph_init(t_intldta *indta, t_graph *g)
{
	g->scale_rec++;
	g->min_x = indta->rooms->x_cord;
	g->min_y = indta->rooms->y_cord;
	g->max_x = indta->rooms->x_cord;
	g->max_y = indta->rooms->y_cord;
	set_limits(indta, g);
	ft_printf("x_min: %d x_max: %d\ny_min: %d y_max: %d\n", g->min_x, g->max_x, g->min_y, g->max_y);
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
		graph_init(indta, g);
	}
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

static void	set_map_transparent(t_vis_prms *v)
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

static void	build_graph(t_intldta *indta, t_graph *g, t_find_way *find)
{
	t_way		**way;
	t_dllist	*room;
	t_list		*ptr;

	draw_links(indta, g);
	draw_rooms(indta, g);
	mlx_put_image_to_window(g->graph->mlx_ptr, g->graph->win_ptr, g->graph->img_ptr, 0, 0);
	ptr = find->answer->ways;
	g->route_color = ROUTE_COLOR;
	while (ptr)
	{
		way = ptr->content;
		room = (*way)->rooms;
		set_map_transparent(g->mask);
		//change graph to mask
		build_route(g, room);
		mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->mask->img_ptr, 0, 0);
		g->route_color += 1500000;
		ptr = ptr->next;
	}
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
	graph_init(indta, &g);
	window_init(&v, &mask, &graph);
	build_graph(indta, &g, find);
	//mlx_put_image_to_window(graph.mlx_ptr, graph.win_ptr, graph.img_ptr, 0, 0);
	mlx_hook(v.win_ptr, 2, 0, &deal_key, (void*)(&v));
	mlx_hook(v.win_ptr, 17, 0, &close_vis, (void*)(&v));
	//mlx_loop_hook(graph.mlx_ptr, &get_command, (void*)(&graph));
	mlx_loop(v.mlx_ptr);
}
