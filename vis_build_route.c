/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_build_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:54:33 by uhand             #+#    #+#             */
/*   Updated: 2019/08/27 14:36:33 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*static float set_cur_thick(t_draw_thick *tk, t_line_prm *l, t_dot_prm *a, \
	t_dot_prm *b)
{
	float			cur;

	if (tk->thick)
		return (tk->thick);
	cur = a->thickness + ((l->i * (b->thickness - a->thickness)) / \
		ft_abs(l->d_big));
	return (cur);
}

static void	get_thick(t_draw_thick *tk, t_line_prm *l, t_dot_prm *a, \
	t_dot_prm *b)
{
	//
}

void		build_thick_line(t_line_prm *l, t_dot_prm *a, t_dot_prm *b, \
	t_grad_prms *clr)
{
	t_draw_thick	tk;

	if (a->thickness == b->thickness)
		tk.thick = a->thickness;
	else
		tk.thick = 0;
	if (tk.thick)
		get_thick(&tk, l, a, b);
	while (l->i <= ft_abs(l->d_big))
	{
		if (!tk.thick)
			get_thick(&tk, l, a, b);
		if (l->d_ind == 1)
			//
		else
			//
		build_line(&tk.l, &tk.n, &tk.gr, &put_pix_to_img);
		l->i++;
	}
}

void		build_route(t_graph *g, t_find_way *find)
{
	//
}*/
