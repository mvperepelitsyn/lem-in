/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:00:49 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 16:44:54 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		put_pix_to_img(t_line_prm *l, int x, int y, int color)
{
	int	*image;

	if (x < 0 || y < 0 || x >= l->img->win_x || y >= l->img->win_y)
		return (0);
	image = (int*)l->img->img_addr;
	image[(y * (l->img->lsz / 4)) + x] = color;
	return (0);
}

void	set_limits(t_intldta *indta, t_graph *g)
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
		if (g->scale_rec <= 2)
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

void	sign_rooms(t_intldta *indta, t_graph *g)
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

void	mix_maps(t_vis_prms *src, t_vis_prms *dst, unsigned char transparency)
{
	t_mix_maps		m;

	if ((m.img_len = src->win_x * src->win_y) != (dst->win_x * dst->win_y))
		return ;
	m.pix_src = (unsigned int*)src->img_addr;
	m.pix_dst = (unsigned int*)dst->img_addr;
	m.start = (src->ndn == 0) ? 0 : 1;
	m.alpha = (src->ndn == 0) ? 3 : 0;
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

void	set_map_transparent(t_vis_prms *v)
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
