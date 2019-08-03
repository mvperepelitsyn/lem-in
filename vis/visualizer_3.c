#include "visualizer.h"

int			get_grad_color(t_vis_prms *v, t_grad_prms *clr, int pos)
{
	t_grad			grad;

	if (clr->a == clr->b || pos == 0)
		return (clr->a);
	if (v->ndn == 0)
	{
		grad.start = 0;
		grad.alpha = 3;
	}
	else
	{
		grad.start = 1;
		grad.alpha = 0;
	}
	set_grad_color(&grad, clr, pos);
	return (grad.color);
}

static void	get_delta(t_pix_prm *a, t_pix_prm *b, t_line_prm *l)
{
	l->d_ind = 0;
	l->dx = b->x - a->x;
	l->dy = b->y - a->y;
	if (ft_abs(l->dx) > ft_abs(l->dy))
	{
		l->d_big = l->dx;
		l->d_small = l->dy;
		l->d_ind = 1;
	}
	else
	{
		l->d_big = l->dy;
		l->d_small = l->dx;
	}
	if (l->d_big < 0)
		l->sign = -1;
	else
		l->sign = 1;
}

static int	get_coord(t_line_prm *l)
{
	int				coord;
	int				sign;

	if (l->d_small < 0)
		sign = -1;
	else
		sign = 1;
	if (l->i == ft_abs(l->d_big))
		return (l->d_small);
	coord = (((l->d_small * l->i) * 100) / ft_abs(l->d_big));
	if (ft_abs(coord % 100) > 50)
		coord = ((coord / 100) + (1 * sign));
	else
		coord /= 100;
	return (coord);
}

static void	build_line(t_line_prm *l, t_pix_prm *a, t_grad_prms *clr)
{
	while (l->i <= ft_abs(l->d_big))
	{
		if (l->d_ind == 1)
			put_pix_to_img(l, (a->x + (l->i * l->sign)), \
				(a->y + get_coord(l)), get_grad_color(l->img, clr, l->i));
		else
			put_pix_to_img(l, (a->x + get_coord(l)), \
				(a->y + (l->i * l->sign)), get_grad_color(l->img, clr, l->i));
		l->i++;
	}
}

void		put_line_to_img(t_vis_prms *v, t_pix_prm a, t_pix_prm b)
{
	t_line_prm		l;
	t_grad_prms		clr;

	if (a.x == b.x && a.y == b.y)
		return ;
	if (((a.x < 0 || a.x >= v->win_x) || (a.y < 0 || a.y >= v->win_y)) \
		&& ((b.x < 0 || b.x >= v->win_x) || (b.y < 0 || b.y >= v->win_y)))
		return ;
	get_delta(&a, &b, &l);
	if (l.d_big == 0)
		return ;
	clr.delta = ft_abs(l.d_big);
	clr.a = a.color;
	clr.b = b.color;
	l.i = 0;
	l.img = v;
	build_line(&l, &a, &clr);
}
