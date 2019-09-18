/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:46:45 by uhand             #+#    #+#             */
/*   Updated: 2019/09/17 17:46:52 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		deal_key(int key, void *prm)
{
	t_graph		*g;
	static int	i;

	g = (t_graph*)prm;
	if (key == 53)
		return (close_vis(prm));
	else if (key == 124 && !g->run)
	{
		if (g->set_ptr->next && !i)
			g->set_ptr = g->set_ptr->next;
		else
		{
			g->set_ptr = g->find->answer;
			i = 1;
		}
		g->mode = 0;
		g->step_ptr = NULL;
		build_graph(g->indta, g, g->find);
	}
	else if (key == 123 && g->set_ptr->prev && !g->run)
	{
		g->set_ptr = g->set_ptr->prev;
		if (i)
			i = 0;
		g->mode = 0;
		g->step_ptr = NULL;
		build_graph(g->indta, g, g->find);
	}
	if (key == 36 && g->set_ptr == g->find->answer)
	{
		g->run = (!g->run) ? 1 : 0;
		g->mode = 1;
	}
	if (key == 34)
		g->info = (!g->info) ? 1 : 0;
	return (0);
}

int		close_vis(void *prm)
{
	t_graph	*g;

	g = (t_graph*)prm;
	mlx_destroy_image(g->v->mlx_ptr, g->v->img_ptr);
	mlx_destroy_window(g->v->mlx_ptr, g->v->win_ptr);
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
