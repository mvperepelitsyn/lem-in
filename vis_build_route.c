/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_build_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:54:33 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 17:00:03 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		build_thick_line(t_line_prm *l, t_dot_prm *a, t_circle *c)
{
	t_draw_thick	tk;

	tk.l.img = l->img;
	while (l->i <= ft_abs(l->d_big))
	{
		if (l->d_ind == 1)
		{
			tk.x = a->x + (l->i * l->sign);
			tk.y = a->y + get_coord(l);
		}
		else
		{
			tk.x = a->x + get_coord(l);
			tk.y = a->y + (l->i * l->sign);
		}
		c->x = tk.x;
		c->y = tk.y;
		draw_circle(c, l->img, 1, &put_pix_to_img);
		l->i++;
	}
}

static void	dot_init(t_build_route *br, t_circle *c)
{
	get_delta(&br->a, &br->b, &br->l);
	br->l.i = 0;
	br->clr.delta = ft_abs(br->l.d_big);
	br->clr.a = br->a.color;
	br->clr.b = br->b.color;
	c->clr = br->a.color;
	c->x = br->a.x;
	c->y = br->a.y;
}

void		build_route(t_graph *g, t_dllist *room)
{
	t_build_route	br;
	t_circle		c;

	br.l.img = g->mask;
	br.a.thick = ROUTE_THICK;
	br.b.thick = ROUTE_THICK;
	br.a.color = g->route_color;
	br.b.color = g->route_color;
	c.r = ROUTE_THICK / 2;
	while (room->right)
	{
		br.croom = room->content;
		br.a.x = ((*br.croom)->x_cord * g->scale) + (2 * R) + LINE_H;
		br.a.y = ((*br.croom)->y_cord * g->scale) + (2 * R) + LINE_H;
		br.croom = room->right->content;
		br.b.x = ((*br.croom)->x_cord * g->scale) + (2 * R) + LINE_H;
		br.b.y = ((*br.croom)->y_cord * g->scale) + (2 * R) + LINE_H;
		dot_init(&br, &c);
		build_thick_line(&br.l, &br.a, &c);
		room = room->right;
	}
	c.x = ((*br.croom)->x_cord * g->scale) + (2 * R) + LINE_H;
	c.y = ((*br.croom)->y_cord * g->scale) + (2 * R) + LINE_H;
}
