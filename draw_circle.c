/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:51:10 by uhand             #+#    #+#             */
/*   Updated: 2019/08/31 19:01:55 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	fill_square(t_circle *c, t_line_prm *l)
{
	int			x;
	int			y;

	x = - (int)c->eighth;
	while (x < (int)c->eighth)
	{
		y = - (int)c->eighth;
		while (y < (int)c->eighth)
		{
			put_pix_to_img(l, (c->x + x), (c->y + y), c->clr);
			y++;
		}
		x++;
	}
}

static void	fill_circle(t_circle *c, t_line_prm *l)
{
	int			i;

	i = 0;
	while (i < (int)c->xo)
	{
		put_pix_to_img(l, (c->x + i), (c->y + (int)c->yo), c->clr);
		put_pix_to_img(l, (c->x - i), (c->y + (int)c->yo), c->clr);
		put_pix_to_img(l, (c->x + i), (c->y - (int)c->yo), c->clr);
		put_pix_to_img(l, (c->x - i), (c->y - (int)c->yo), c->clr);
		put_pix_to_img(l, (c->x + (int)c->yo), (c->y + i), c->clr);
		put_pix_to_img(l, (c->x - (int)c->yo), (c->y + i), c->clr);
		put_pix_to_img(l, (c->x + (int)c->yo), (c->y - i), c->clr);
		put_pix_to_img(l, (c->x - (int)c->yo), (c->y - i), c->clr);
	}
}

void		draw_circle(t_circle *c, t_vis_prms *v, int fill_prm)
{
	t_line_prm	l;

	l.img = v;
	c->xo = 0;
	c->eighth = (sqrt(2) / 2) * c->r;
	while (c->xo <= c->eighth)
	{
		c->yo = sqrt((c->r * c->r) - (c->xo * c->xo));
		if ((c->yo - (int)c->yo) > 0.5)
			c->yo++;
		put_pix_to_img(&l, (c->x + (int)c->xo), (c->y + (int)c->yo), c->clr);
		put_pix_to_img(&l, (c->x - (int)c->xo), (c->y + (int)c->yo), c->clr);
		put_pix_to_img(&l, (c->x + (int)c->xo), (c->y - (int)c->yo), c->clr);
		put_pix_to_img(&l, (c->x - (int)c->xo), (c->y - (int)c->yo), c->clr);
		put_pix_to_img(&l, (c->x + (int)c->yo), (c->y + (int)c->xo), c->clr);
		put_pix_to_img(&l, (c->x - (int)c->yo), (c->y + (int)c->xo), c->clr);
		put_pix_to_img(&l, (c->x + (int)c->yo), (c->y - (int)c->xo), c->clr);
		put_pix_to_img(&l, (c->x - (int)c->yo), (c->y - (int)c->xo), c->clr);
		if (fill_prm)
			fill_circle(c, &l);
		c->xo++;
	}
	if (fill_prm)
		fill_square(c, &l);
}
