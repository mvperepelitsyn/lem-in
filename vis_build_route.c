/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_build_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:54:33 by uhand             #+#    #+#             */
/*   Updated: 2019/09/17 10:57:04 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		mix_pix_in_img(t_line_prm *l, int x, int y, int color)
{
	unsigned int	*image;
	int				start;
	int				alpha;
	int				coord;
	int				i;
	unsigned char	*cnl_dst;
	unsigned char	*cnl_src;

	if (x < 0 || y < 0 || x >= l->img->win_x || y >= l->img->win_y)
		return (0);
	image = (unsigned int*)l->img->img_addr;
	coord = (y * (l->img->lsz / 4)) + x;
	start = (l->img->ndn == 0) ? 0 : 1;
	alpha  = (l->img->ndn == 0) ? 3 : 0;
	i = 0;
	cnl_dst = (unsigned char*)&image[coord];
	cnl_src = (unsigned char*)&color;
	//ft_printf("%X ", (unsigned int)image[coord]);
	 ft_printf("%X %X %X %X : ", (unsigned int)cnl_dst[0], (unsigned int)cnl_dst[1], (unsigned int)cnl_dst[2], (unsigned int)cnl_dst[3]);
	if (!cnl_dst[start] && !cnl_dst[start + 1] && !cnl_dst[start + 2])
		return (image[coord] = color);
	// ft_printf("%X : %X : ", image[coord], color);
	/*while (i < 3)
	{
		cnl_dst[start + i] = (cnl_dst[start + i] / 2) + (cnl_src[start + i] / 2);
		i++;
	}
	cnl_dst[alpha] = cnl_src[alpha];*/
	// ft_printf("%X\n", image[coord]);
	image[coord] = 0xFFFF00FF;
	ft_printf("%X %X %X %X | ", (unsigned int)cnl_dst[0], (unsigned int)cnl_dst[1], (unsigned int)cnl_dst[2], (unsigned int)cnl_dst[3]);
	return (0);
}

void	build_thick_line(t_line_prm *l, t_dot_prm *a, t_dot_prm *b, \
	t_grad_prms *clr, t_circle *c)
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
