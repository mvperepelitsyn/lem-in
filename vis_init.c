/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:27:28 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 18:26:42 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void		pre_coord_init(t_intldta *indta, t_graph *g, t_crd_init *c)
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
	c->dx = ((long long)g->max_x - (long long)g->min_x) * (long long)g->scale;
	c->dy = ((long long)g->max_y - (long long)g->min_y) * (long long)g->scale;
}

void		coord_init(t_intldta *indta, t_graph *g)
{
	static int		redef;
	t_crd_init		c;

	pre_coord_init(indta, g, &c);
	while ((g->delta_x + (R * 4) + LINE_H * 2) > WIN_X || \
		(g->delta_y + (R * 4) + LINE_H * 2) > WIN_Y || \
		(long long)g->delta_x != c.dx || (long long)g->delta_y != c.dy || \
		(g->delta_x + (R * 4) + LINE_H * 2) < c.dx || \
		(g->delta_y + (R * 4) + LINE_H * 2) < c.dy)
	{
		if (!g->scale)
			break ;
		g->scale--;
		g->delta_x = (g->max_x - g->min_x) * g->scale;
		g->delta_y = (g->max_y - g->min_y) * g->scale;
		c.dx = ((long long)g->max_x - (long long)g->min_x) * (long long)g->scale;
		c.dy = ((long long)g->max_y - (long long)g->min_y) * (long long)g->scale;
	}
	if ((!g->scale && g->scale_rec < 2) || (indta->r_flag && !redef))
	{
		redef++;
		coord_redef(indta, g);
		coord_init(indta, g);
	}
}

void		graph_init(t_graph *g, t_find_way *find, t_intldta *indta)
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

void		window_init(t_vis_prms *v, t_vis_prms *mask, t_vis_prms *graph, \
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
