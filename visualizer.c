/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 12:22:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		sign_rooms(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;
	t_circle		c;
	unsigned int	color;

	ptr = indta->rooms;
	c.r = R;
	while (ptr)
	{
		c.x = (ptr->x_cord * g->scale) + (2 * R) + LINE_H;
		c.y = (ptr->y_cord * g->scale) + (2 * R) + LINE_H;

		color = (ptr->act_lnks > 0) ? 0xFF0000 : 0x555555;
		mlx_string_put(g->graph->mlx_ptr, g->graph->win_ptr, (c.x - R), \
			(c.y + R * 2), color, ptr->name);
		ptr = ptr->next;
	}
}

static void	mix_maps(t_vis_prms *src, t_vis_prms *dst, \
	unsigned char transparency)
{
	t_mix_maps		m;

	if ((m.img_len = src->win_x * src->win_y) != (dst->win_x * dst->win_y))
		return ;
	m.pix_src = (unsigned int*)src->img_addr;
	m.pix_dst = (unsigned int*)dst->img_addr;
	m.start = (src->ndn == 0) ? 0 : 1;
	m.alpha  = (src->ndn == 0) ? 3 : 0;
	m.i = 0;
	while (m.i < m.img_len)
	{
		m.j = 0;
		m.byte_src = (unsigned char*)&m.pix_src[m.i];
		m.byte_dst = (unsigned char*)&m.pix_dst[m.i];
		while (m.j < 3)
		{
			if (m.byte_src[m.start + m.j] != m.byte_dst[m.start + m.j])
				m.byte_dst[m.start + m.j] = (m.byte_dst[m.start + m.j] / 2) + \
				(m.byte_src[m.start + m.j] / 2);
			m.j++;
		}
		m.byte_dst[m.alpha] = transparency;
		m.i++;
	}
}

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
	static int		redef;
	long long		dx;
	long long		dy;

	g->scale_rec++;
	g->min_x = indta->rooms->x_cord;
	g->min_y = indta->rooms->y_cord;
	g->max_x = indta->rooms->x_cord;
	g->max_y = indta->rooms->y_cord;
	set_limits(indta, g);
	g->scale = SCALE;
	g->delta_x = (g->max_x - g->min_x) * g->scale;
	g->delta_y = (g->max_y - g->min_y) * g->scale;
	dx = (g->max_x - g->min_x) * g->scale;
	dy = (g->max_y - g->min_y) * g->scale;
	while ((g->delta_x + (R * 4) + LINE_H * 2) > WIN_X 	|| \
		(g->delta_y + (R * 4) + LINE_H * 2) > WIN_Y || (long long)g->delta_x != dx || \
		(long long)g->delta_y != dy || (g->delta_x + (R * 4) + LINE_H * 2) < dx || \
		(g->delta_y + (R * 4) + LINE_H * 2) < dy)
	{
		if (!g->scale)
			break ;
		g->scale--;
		g->delta_x = (g->max_x - g->min_x) * g->scale;
		g->delta_y = (g->max_y - g->min_y) * g->scale;
	}
	if ((!g->scale && g->scale_rec < 2) || (indta->r_flag && !redef))
	{
		redef++;
		coord_redef(indta, g);
		coord_init(indta, g);
	}
}

static void	graph_init(t_graph *g, t_find_way *find, t_intldta *indta)
{
	g->v->win_x = g->delta_x + (R * 4) + LINE_H * 2;
	g->v->win_y = g->delta_y + (R * 4) + LINE_H * 2;
	g->mask->win_x = g->v->win_x;
	g->mask->win_y = g->v->win_y;
	g->graph->win_x = g->v->win_x;
	g->graph->win_y = g->v->win_y;
	g->route->win_x = g->v->win_x;
	g->route->win_y = g->v->win_y;
	g->clr[0] = R_CLR;
	g->clr[1] = S_CLR;
	g->clr[2] = F_CLR;
	g->set_ptr = find->sets;
	g->indta = indta;
	g->find = find;
}

static void	window_init(t_vis_prms *v, t_vis_prms *mask, t_vis_prms *graph, \
	t_vis_prms *route)
{
	v->mlx_ptr = mlx_init();
	mask->mlx_ptr = v->mlx_ptr;
	graph->mlx_ptr = v->mlx_ptr;
	route->mlx_ptr = v->mlx_ptr;

	v->win_ptr = mlx_new_window(v->mlx_ptr, v->win_x, v->win_y, "Lem_in");
	mask->win_ptr = v->win_ptr;
	graph->win_ptr = v->win_ptr;
	route->win_ptr = v->win_ptr;

	v->img_ptr = mlx_new_image(v->mlx_ptr, v->win_x, v->win_y);
	v->img_addr = mlx_get_data_addr(v->img_ptr, &v->bpp, &v->lsz, &v->ndn);

	mask->img_ptr = mlx_new_image(mask->mlx_ptr, v->win_x, v->win_y);
	mask->img_addr = mlx_get_data_addr(mask->img_ptr, &mask->bpp, \
		&mask->lsz, &mask->ndn);

	graph->img_ptr = mlx_new_image(graph->mlx_ptr, v->win_x, v->win_y);
	graph->img_addr = mlx_get_data_addr(graph->img_ptr, &graph->bpp, \
		&graph->lsz, &graph->ndn);

	route->img_ptr = mlx_new_image(route->mlx_ptr, v->win_x, v->win_y);
	route->img_addr = mlx_get_data_addr(route->img_ptr, &route->bpp, \
		&route->lsz, &route->ndn);
}

void		set_map_transparent(t_vis_prms *v)
{
	size_t			img_len;
	size_t			i;
	unsigned int	*pixel;

	img_len = v->win_x * v->win_y;
	pixel = (unsigned int*)v->img_addr;
	i = 0;
	while (i < img_len)
	{
		pixel[i] = 0xFF000000;
		i++;
	}
}

void		build_graph(t_intldta *indta, t_graph *g, t_find_way *find)
{
	t_way		**way;
	t_dllist	*room;
	t_list		*ptr;

	draw_links(indta, g);
	draw_rooms(indta, g);
	mlx_clear_window (g->graph->mlx_ptr, g->graph->win_ptr);
	mlx_put_image_to_window(g->graph->mlx_ptr, g->graph->win_ptr, g->graph->img_ptr, 0, 0);
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
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->route->img_ptr, 0, 0);
}

static int	get_command(void *prm)
{
	t_ants			*ants;
	t_graph		*g;
	char		*str;
	int			ant;

	g = (t_graph*)prm;
	if (g->run)
		vis_step(g, g->indta);
	else if (g->mode)
	{
		mlx_clear_window (g->v->mlx_ptr, g->v->win_ptr);
		mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->graph->img_ptr, 0, 0);
		mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->route->img_ptr, 0, 0);
		mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->v->img_ptr, 0, 0);
		ft_sprintf(&str, "step: %d / %d", g->step + 1, g->find->answer->steps);
		mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, 5, 5, 0xFFFFFF, str);
		free(str);
		if (g->info)
			sign_rooms(g->indta, g);
		if(g->step)
		{
			ants = (t_ants*)g->step_ptr->content;
			ant = 0;
			while (ant < g->indta->num_ants && g->frame < FRAMES_COUNT && g->info)
			{
				if (ants[ant].status || (ants[ant].position == g->indta->end_room \
					&& !ants[ant].finished))
					sign_ant_step(ants[ant].rooms, g, g->frame, ants[ant].color, ant);
				ant++;
			}
		}
	}
	else if (!g->mode)
	{
		mlx_clear_window (g->v->mlx_ptr, g->v->win_ptr);
		mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->graph->img_ptr, 0, 0);
		mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->route->img_ptr, 0, 0);
		str = NULL;
		ft_sprintf(&str, "ways: %d, steps: %d", g->set_ptr->ways_cnt, g->set_ptr->steps);
		mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, 5, 5, 0xFFFFFF, str);
		if (g->info)
			sign_rooms(g->indta, g);
		if (g->set_ptr == g->find->answer)
			mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, g->v->win_x - 80, 5, 0x00FF00, "Answer!");
		free(str);
	}
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
	build_graph(indta, &g, find);
	set_map_transparent(g.v);
	mlx_hook(v.win_ptr, 2, 0, &deal_key, (void*)(&g));
	mlx_hook(v.win_ptr, 17, 0, &close_vis, (void*)(&g));
	mlx_loop_hook(graph.mlx_ptr, &get_command, (void*)(&g));
	mlx_loop(v.mlx_ptr);
}
