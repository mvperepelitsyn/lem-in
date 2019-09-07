/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:46:45 by uhand             #+#    #+#             */
/*   Updated: 2019/09/07 16:58:35 by stephan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		deal_key(int key, void *prm)
{
	t_vis_prms	*v;

	v = (t_vis_prms*)prm;
	ft_printf("key nbr: %d\n");
	 if (key == 53)
	 	return (close_vis(prm));
	return (0);
}

int		close_vis(void *prm)
{
	t_vis_prms	*v;

	// v = (t_vis_prms*)prm;
	// mlx_destroy_image(v->mlx_ptr, v->img_ptr);
	// mlx_destroy_window(v->mlx_ptr, v->win_ptr);
	exit(0);
	return (0);
}

void	trim_line(t_dot_prm *a, t_dot_prm *b, int r)
{
	double	dx;
	double	dy;
	double	n;

	dx = b->x - a->x;
	dy = b->y - a->y;
	n = r / sqrt((dx * dx) + (dy * dy));
	dx *= n;
	dy *= n;
	if ((dx - (int)dx) > 0.5)
		dx++;
	if ((dy - (int)dy) > 0.5)
		dy++;
	a->x += (int)dx;
	a->y += (int)dy;
	b->x -= (int)dx;
	b->y -= (int)dy;
}
