/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:04:58 by uhand             #+#    #+#             */
/*   Updated: 2019/09/16 18:54:58 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ant_color_init(t_ants **ants, int ants_count)
{
	int		i;
	int		color;

	i = 0;
	color = 0x000088;
	while (i < ants_count)
	{
		ants[i]->color = color;
		i++;
		color += ANT_CLR_BUMP;
		if (color > 0xFFFFFF)
			color = 0x000088;
	}
}

static void	draw_ant_step(t_dllist *room, t_graph *g, int frame, int color)
{
	t_draw_ant	ant;
	t_circle	c;

	ant.b = ((t_list_rooms**)(room->content))[0];
	ant.a = ((t_list_rooms**)room->left->content)[0];
	c.x = ((float)(ant.b->x_cord - ant.a->x_cord) / FRAMES_COUNT) * frame \
		+ ant.a->x_cord;
	c.y = ((float)(ant.b->y_cord - ant.a->y_cord) / FRAMES_COUNT) * frame \
		+ ant.a->y_cord;
	c.r = ANT_R;
	c.clr = color;
	draw_circle(&c, g->v, 1, &put_pix_to_img);
}

void	vis_step(t_ants **ants, t_graph *g, t_intldta *indta)
{
	int		frames_count;
	int		frame;
	int		ant;

	frame = 0;
	frames_count = FRAMES_COUNT;
	while (frame < frames_count)
	{
		ant = 0;
		while (ant < indta->num_ants)
		{
			if (ants[ant]->status || (ants[ant]->position == indta->end_room \
				&& !ants[ant]->finished))
				draw_ant_step(ants[ant]->rooms, g, frame, ants[ant]->color);
			ant++;
		}
		//mlx_put_image_to_window();
		frame++;
	}
}
