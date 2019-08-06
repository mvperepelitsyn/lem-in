/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/08/06 17:51:55 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	set_limits(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;

	ptr = indta->rooms->next;
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
		ptr = ptr->next;
	}
}

static void	graph_init(t_intldta *indta, t_graph *g, t_vis_prms *v)
{
	g->min_x = indta->rooms->x_cord;
	g->min_y = indta->rooms->y_cord;
	g->max_x = indta->rooms->x_cord;
	g->max_y = indta->rooms->y_cord;
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
	v->win_x = g->delta_x + (R * 2);
	v->win_y = g->delta_y + (R * 2);
	g->v = v;
	g->clr[0] = R_CLR;
	g->clr[1] = S_CLR;
	g->clr[2] = F_CLR;
}

static void	window_init(t_vis_prms *v)
{
	v->mlx_ptr = mlx_init();
	v->win_ptr = mlx_new_window(v->mlx_ptr, v->win_x, v->win_y, "Lem_in");
	v->img_ptr = mlx_new_image(v->mlx_ptr, v->win_x, v->win_y);
	v->img_addr = mlx_get_data_addr(v->img_ptr, &v->bpp, &v->lsz, &v->ndn);
}

static void	build_graph(t_intldta *indta, t_graph *g)
{
	draw_rooms(indta, g);
	draw_links(indta, g);
}

static int	get_command(void *prm)
{
	t_vis_prms	*v;

	v = (t_vis_prms*)prm;
	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, v->img_ptr, 0, 0);
	return (0);
}

void		visualizer(t_intldta *indta)
{
	t_graph		g;
	t_vis_prms	v;

	if (!indta->rooms)
		return ;
	graph_init(indta, &g, &v);
	window_init(&v);
	build_graph(indta, &g);
	ft_printf("\nlala\n");
	mlx_put_image_to_window(v.mlx_ptr, v.win_ptr, v.img_ptr, 0, 0);
	mlx_loop_hook(v.mlx_ptr, &get_command, (void*)(&v));
	mlx_loop(v.mlx_ptr);
}
