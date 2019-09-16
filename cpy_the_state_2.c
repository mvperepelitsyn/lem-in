/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_the_state_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:55:44 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/16 17:22:52 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	helper_cpy_the_rooms(t_list_rooms *s, t_list_rooms *d)
{
	d->status = s->status;
	d->num_lnks = s->num_lnks;
	d->x_cord = s->x_cord;
	d->y_cord = s->y_cord;
	d->type = s->type;
	d->step_nbr = s->step_nbr;
	d->tmp_step_nbr = s->tmp_step_nbr;
	d->way_nbr = s->way_nbr;
}

void		cpy_the_rooms(t_list_rooms *s_rms, t_list_rooms **d_rms)
{
	t_list_rooms *s;
	t_list_rooms *d;
	t_list_rooms *tmp;

	s = s_rms;
	tmp = NULL;
	while (s)
	{
		*d_rms = (t_list_rooms *)ft_memalloc(sizeof(t_list_rooms));
		if (tmp)
		{
			(*d_rms)->prev = tmp;
			(*d_rms)->prev->next = (*d_rms);
		}
		else
			d = (*d_rms);
		(*d_rms)->act_lnks = s->act_lnks;
		(*d_rms)->name = ft_strsub(s->name, 0, ft_strlen(s->name));
		helper_cpy_the_rooms(s, (*d_rms));
		tmp = (*d_rms);
		(*d_rms) = (*d_rms)->next;
		s = s->next;
	}
	(*d_rms) = d;
}

static void	helper_cpy_the_links(t_list_rooms *tmp, t_list_links *d_lnks,
		t_list_rooms *rms, t_list_links *s)
{
	d_lnks->room1 = ft_strsub(s->room1, 0, ft_strlen(s->room1));
	d_lnks->room2 = ft_strsub(s->room2, 0, ft_strlen(s->room2));
	while (!ft_strequ(s->room1, tmp->name))
		tmp = tmp->next;
	d_lnks->rm1 = tmp;
	tmp = rms;
	while (!ft_strequ(s->room2, tmp->name))
		tmp = tmp->next;
	d_lnks->rm2 = tmp;
	d_lnks->sttus = d_lnks->sttus;
	d_lnks->way_nbr = s->way_nbr;
}

void		cpy_the_links(t_list_links *s_lnks, t_list_links **d_lnks,
		t_list_rooms *rms)
{
	t_list_links	*s;
	t_list_links	*d;
	t_list_rooms	*tmp;
	int				cnt;
	t_list_links	*tmp_l;

	s = s_lnks;
	tmp = rms;
	cnt = 0;
	tmp_l = NULL;
	while (s)
	{
		tmp = rms;
		(*d_lnks) = (t_list_links *)ft_memalloc(sizeof(t_list_links));
		if (tmp_l)
			tmp_l->next = *d_lnks;
		if (cnt == 0)
			d = *d_lnks;
		helper_cpy_the_links(tmp, *d_lnks, rms, s);
		tmp_l = *d_lnks;
		(*d_lnks) = (*d_lnks)->next;
		s = s->next;
		cnt++;
	}
	*d_lnks = d;
}
