/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:07:33 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 16:43:44 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		set_grad_color(t_grad *g, t_grad_prms *clr, int pos)
{
	g->a = (unsigned char*)&clr->a;
	g->b = (unsigned char*)&clr->b;
	g->d_alpha = (int)g->b[g->alpha] - (int)g->a[g->alpha];
	g->d1 = (int)g->b[g->start] - (int)g->a[g->start];
	g->d2 = (int)g->b[g->start + 1] - (int)g->a[g->start + 1];
	g->d3 = (int)g->b[g->start + 2] - (int)g->a[g->start + 2];
	g->color = 0;
	g->c = (unsigned char*)&(g->color);
	g->c[g->start] = ((g->d1 * pos) / clr->delta) + g->a[g->start];
	g->c[g->start + 1] = ((g->d2 * pos) / clr->delta) + g->a[g->start + 1];
	g->c[g->start + 2] = ((g->d3 * pos) / clr->delta) + g->a[g->start + 2];
	g->c[g->alpha] = ((g->d_alpha * pos) / clr->delta) + g->a[g->alpha];
}

void		transparent(int *color, unsigned char clarity, t_vis_prms *v)
{
	int				alpha;
	unsigned char	*clr;

	alpha = (v->ndn == 0) ? 3 : 0;
	clr = (unsigned char*)color;
	clr[alpha] = clarity;
}

void		draw_rooms(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;
	t_list_rooms	*ptr_set;
	t_circle		c;

	ptr = indta->rooms;
	ptr_set = g->set_ptr->rooms;
	c.r = R;
	while (ptr)
	{
		c.clr = g->clr[ptr->type];
		c.x = (ptr->x_cord * g->scale) + (2 * R) + LINE_H;
		c.y = (ptr->y_cord * g->scale) + (2 * R) + LINE_H;
		if (!ptr->act_lnks)
			transparent(&c.clr, 200, g->graph);
		draw_circle(&c, g->graph, 0, &put_pix_to_img);
		ptr = ptr->next;
		ptr_set = ptr_set->next;
	}
}

static void	set_dots_coords(t_graph *g, t_list_links *ptr, t_dot_prm *a, \
	t_dot_prm *b)
{
	a->x = ptr->rm1->x_cord * g->scale + (2 * R) + LINE_H;
	a->y = ptr->rm1->y_cord * g->scale + (2 * R) + LINE_H;
	a->color = g->clr[ptr->rm1->type];
	a->thick = 1;
	b->x = ptr->rm2->x_cord * g->scale + (2 * R) + LINE_H;
	b->y = ptr->rm2->y_cord * g->scale + (2 * R) + LINE_H;
	b->color = g->clr[ptr->rm2->type];
	b->thick = 1;
}

void		draw_links(t_intldta *indta, t_graph *g)
{
	t_list_links	*ptr;
	t_list_links	*ptr_set;
	t_dot_prm		a;
	t_dot_prm		b;

	ptr = indta->links;
	ptr_set = g->set_ptr->links;
	while (ptr)
	{
		set_dots_coords(g, ptr, &a, &b);
		trim_line(&a, &b, R);
		if (!ptr_set->sttus)
		{
			transparent(&a.color, 200, g->graph);
			transparent(&b.color, 200, g->graph);
		}
		put_line_to_img(g->graph, a, b);
		ptr = ptr->next;
		ptr_set = ptr_set->next;
	}
}
