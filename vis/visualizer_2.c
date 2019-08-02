#include "visualizer.h"

static void	draw_circle(int r, int x, int y, int color)
{
	//
}

void	draw_rooms(t_intldta *indta, t_graph *g)
{
	t_room	*ptr;

	ptr = indta->rooms;
	while (ptr)
	{
		if (ptr->type == 1)
			draw_circle(R, (int)ptr->x_cord, (int)ptr->y_cord, S_CLR);
		else if (ptr->type == 2)
			draw_circle(R, (int)ptr->x_cord, (int)ptr->y_cord, F_CLR);
		else
			draw_circle(R, (int)ptr->x_cord, (int)ptr->y_cord, R_CLR);
		ptr = ptr->next;
	}
}

void	draw_links(t_intldta *indta, t_graph *g)
{
	//
}
