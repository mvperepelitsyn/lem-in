//
// Created by Dwarven centurion Frost atronach on 2019-09-16.
//

#include "lem_in.h"

static void cpy_the_rooms(t_list_rooms *s_rms, t_list_rooms **d_rms)
{
	t_list_rooms *s;
	t_list_rooms *d;
	t_list_rooms *tmp;

	s = s_rms;
	d = *d_rms;
	tmp = NULL;
	while (s)
	{
		d = (t_list_rooms *)ft_memalloc(sizeof(t_list_rooms));
		if (tmp)
			d->prev = tmp;
		d->act_lnks = s->act_lnks;
		d->name = ft_strsub(s->name, 0, ft_strlen(s->name));
		d->status = s->status;
		d->num_lnks = s->num_lnks;
		d->x_cord = s->x_cord;
		d->y_cord = s->y_cord;
		d->type = s->type;
		d->step_nbr = s->step_nbr;
		d->tmp_step_nbr = s->tmp_step_nbr;
		d->way_nbr = s->way_nbr;
		tmp = d;
		d = d->next;
		s = s->next;
	}
}

static void	cpy_the_links(t_list_links *s_lnks, t_list_links **d_lnks,
		t_list_rooms *rms)
{
	t_list_links *s;
	t_list_links *d;
	t_list_rooms *tmp;

	s = s_lnks;
	d = *d_lnks;
	tmp = rms;
	while (s)
	{
		d = (t_list_links *)ft_memalloc(sizeof(t_list_links));
		d->room1 = ft_strsub(s->room1, 0 , ft_strlen(s->room1));
		d->room2 = ft_strsub(s->room2, 0 , ft_strlen(s->room2));

		s = s->next;
	}

}

void	cpy_the_state(t_intldta **inda, t_list_links **lnks, t_list_rooms **rms)
{
	cpy_the_rooms((*inda)->rooms, rms);
	cpy_the_links((*inda)->links, lnks, *rms);
}