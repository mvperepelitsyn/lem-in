/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_build_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:54:33 by uhand             #+#    #+#             */
/*   Updated: 2019/08/30 19:33:16 by uhand            ###   ########.fr       */
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
	tx = (tk->thick / 2) * cos(atan(l->dx / l->dy));
	ty = (tk->thick / 2) * sin(atan(l->dx / l->dy));
	if ((tx - (int)tx) > 0.5)
		tx++;
	if ((ty - (int)ty) > 0.5)
		ty++;
	tk->m.x = - tx;
	tk->m.y = ty;
	tk->n.x = tx;
	tk->n.y = - ty;
}

void	build_thick_line(t_line_prm *l, t_dot_prm *a, t_dot_prm *b, \
	t_grad_prms *clr)
{
	t_draw_thick	tk;

	while (l->i <= ft_abs(l->d_big))
	{
		get_thick(&tk, l, a, b);
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
		tk.m.x += tk.x;
		tk.m.y += tk.y;
		tk.n.x += tk.x;
		tk.n.y += tk.y;
		tk.gr.delta = ft_abs(l->d_big);
		tk.gr.a = get_grad_color(l->img, clr, l->i);
		tk.gr.b = tk.gr.a;
		build_line(&tk.l, &tk.n, &tk.gr, &put_pix_to_img);
		l->i++;
	}
}

static void	dot_init(t_line_prm *l, t_dot_prm *a, t_dot_prm *b, \
	t_grad_prms *clr)
{
	get_delta(a, b, l);
	l->i = 0;
	clr->delta = ft_abs(l->d_big);
	clr->a = a->color;
	clr->b = b->color;
}

void		build_route(t_graph *g, t_dllist *room)
{
	t_build_route	br;

	br.l.img = g->v;
	br.a.thick = ROUTE_THICK;
	br.b.thick = ROUTE_THICK;
	br.a.color = ROUTE_COLOR;
	br.b.color = ROUTE_COLOR;
	while(room->right)
	{
		br.croom = (t_list_rooms*)room->content;
		br.a.x = br.croom->x_cord;
		br.a.y = br.croom->y_cord;
		br.croom = (t_list_rooms*)room->right->content;
		br.b.x = br.croom->x_cord;
		br.b.y = br.croom->y_cord;
		dot_init(&br.l, &br.a, &br.b, &br.clr);
		build_thick_line(&br.l, &br.a, &br.b, &br.clr);
		room = room->right;
	}
}
