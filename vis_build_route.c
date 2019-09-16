/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_build_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:54:33 by uhand             #+#    #+#             */
/*   Updated: 2019/09/13 11:32:29 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_thick(t_draw_thick *tk, t_line_prm *l, t_dot_prm *a, \
	t_dot_prm *b)
{
	float			tx;
	float			ty;

	if (a->thick == b->thick)
		tk->thick = a->thick;
	else
		tk->thick = a->thick + ((l->i * (b->thick - a->thick)) / l->d_big);
	tx = ft_abs((tk->thick / 2) * cos(atan(l->dx / l->dy)));
	ty = ft_abs((tk->thick / 2) * sin(atan(l->dx / l->dy)));
	if ((tx - (int)tx) > 0.5)
		tx++;
	if ((ty - (int)ty) > 0.5)
		ty++;
	tk->m.x = - tx;
	tk->m.y = - ty;
	tk->n.x = + tx;
	tk->n.y = + ty;
}

void	build_thick_line(t_line_prm *l, t_dot_prm *a, t_dot_prm *b, \
	t_grad_prms *clr, t_circle *c)
{
	t_draw_thick	tk;

	// ft_printf("big: %d ", l->d_big);
	// ft_printf("%d\n", l->i);
	tk.l.img = l->img;
	while (l->i <= ft_abs(l->d_big))
	{
		// ft_printf("%d\n", l->i);
		//get_thick(&tk, l, a, b);
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
		/*tk.m.x += tk.x;
		tk.m.y += tk.y;
		tk.n.x += tk.x;
		tk.n.y += tk.y;
		ft_printf("%d ", tk.m.x);
		ft_printf("%d ", tk.m.y);
		ft_printf("%d ", tk.n.x);
		ft_printf("%d\n", tk.n.y);
		get_delta(&tk.m, &tk.n, &tk.l);
		tk.l.i = 0;
		tk.gr.delta = ft_abs(tk.l.d_big);
		tk.gr.a = get_grad_color(tk.l.img, clr, tk.l.i);
		tk.gr.b = tk.gr.a;
		build_line(&tk.l, &tk.m, &tk.gr, &put_pix_to_img);*/
		draw_circle(c, l->img, 1);
		l->i++;
	}
}

static void	dot_init(t_build_route *br, t_circle *c)
{
	get_delta(&br->a, &br->b, &br->l);
	br->l.i = 0/*ft_abs(br->l.d_big) - 1*/;
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
	while(room->right)
	{
		br.croom = room->content;
		br.a.x = ((*br.croom)->x_cord * g->scale)  + (2 * R);
		br.a.y = ((*br.croom)->y_cord * g->scale)  + (2 * R);
		br.croom = room->right->content;
		br.b.x = ((*br.croom)->x_cord * g->scale)  + (2 * R);
		br.b.y = ((*br.croom)->y_cord * g->scale)  + (2 * R);
		dot_init(&br, &c);
		//draw_circle(&c, g->graph, 1);
		build_thick_line(&br.l, &br.a, &br.b, &br.clr, &c);
		room = room->right;
	}
	c.x = ((*br.croom)->x_cord * g->scale)  + (2 * R);
	c.y = ((*br.croom)->y_cord * g->scale)  + (2 * R);
	//draw_circle(&c, g->graph, 1);
}
