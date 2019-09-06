#include "lem_in.h"

int			put_pix_to_img(t_line_prm *l, int x, int y, int color)
{
	int	*image;

	if (x < 0 || y < 0 || x >= l->img->win_x || y >= l->img->win_y)
		return (0);
	image = (int*)l->img->img_addr;
	image[(y * (l->img->lsz / 4)) + x] = color;
	return (0);
}

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

void		draw_rooms(t_intldta *indta, t_graph *g)
{
	t_list_rooms	*ptr;
	t_circle		c;

	ptr = indta->rooms;
	c.r = R;
	while (ptr)
	{
		c.clr = g->clr[ptr->type];
		c.x = (ptr->x_cord * g->scale) + (2 * R);
		c.y = (ptr->y_cord * g->scale) + (2 * R);
		draw_circle(&c, g->graph, 0);
		ptr = ptr->next;
	}
}

void	transparent(int *color, unsigned char clarity, t_vis_prms *v)
{
	int				alpha;
	unsigned char	*clr;

	alpha  = (v->ndn == 0) ? 3 : 0;
	clr = (unsigned char*)color;
	clr[alpha] = clarity;
}

void		draw_links(t_intldta *indta, t_graph *g)
{
	t_list_links	*ptr;
	t_dot_prm		a;
	t_dot_prm		b;

	ptr = indta->links;
	while (ptr)
	{
		a.x = ptr->rm1->x_cord * g->scale + (2 * R);
		a.y = ptr->rm1->y_cord * g->scale + (2 * R);
		a.color =  g->clr[ptr->rm1->type];
		a.thick = 1;
		b.x = ptr->rm2->x_cord * g->scale + (2 * R);
		b.y = ptr->rm2->y_cord * g->scale + (2 * R);
		b.color =  g->clr[ptr->rm2->type];
		b.thick = 1;
		trim_line(&a, &b, R);
		if (!ptr->status)
		{
			transparent(&a.color, 200, g->graph);
			transparent(&b.color, 200, g->graph);
			ft_printf("lala\n");
		}
		put_line_to_img(g->graph, a, b);
		ptr = ptr->next;
	}
}
