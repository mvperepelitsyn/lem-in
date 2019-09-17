/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:04:58 by uhand             #+#    #+#             */
/*   Updated: 2019/09/17 12:06:19 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ant_color_init(t_ants *ants, int ants_count)
{
	int		i;
	int		color;

	ft_printf("l");
	i = 0;
	color = 0x000088;
	while (i < ants_count)
	{
		ants[i].color = color;
		ft_printf("%X\n", ants[i].color);
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
	c.x = (((float)(ant.b->x_cord - ant.a->x_cord) / FRAMES_COUNT) * frame \
		+ ant.a->x_cord) * g->scale  + (2 * R);
	c.y = (((float)(ant.b->y_cord - ant.a->y_cord) / FRAMES_COUNT) * frame \
		+ ant.a->y_cord) * g->scale  + (2 * R);
	c.r = ANT_R;
	c.clr = color;
	draw_circle(&c, g->v, 1, &put_pix_to_img);
}

void	vis_step(t_graph *g, t_intldta *indta)
{
	static int		frame;
	static t_list	*step_ptr;
	static int		step;
	t_ants			*ants;
	int				ant;
	char			*str;

	if (!step_ptr)
		step_ptr = g->find->ants_state;
	// ft_printf("Step: %d\n", step);
	ft_sprintf(&str, "step: %d", step + 1);
	ant = 0;
	ants = (t_ants*)step_ptr->content;
	set_map_transparent(g->v);
	mlx_clear_window (g->v->mlx_ptr, g->v->win_ptr);
	while (ant < indta->num_ants)
	{
		if (ants[ant].status || (ants[ant].position == indta->end_room \
			&& !ants[ant].finished))
			draw_ant_step(ants[ant].rooms, g, frame, ants[ant].color);
		ant++;
	}
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->graph->img_ptr, 0, 0);
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->mask->img_ptr, 0, 0);
	mlx_put_image_to_window(g->v->mlx_ptr, g->v->win_ptr, g->v->img_ptr, 0, 0);
	mlx_string_put(g->v->mlx_ptr, g->v->win_ptr, 5, 5, 0xFFFFFF, str);
	usleep(100);
	frame++;
	if (frame > FRAMES_COUNT)
	{
		frame = 0;
		step_ptr = step_ptr->next;
		step++;
	}
	free(str);
}
