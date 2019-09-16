/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_the_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:55:44 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/16 15:35:04 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	links_assignment(t_list_rooms **rms, t_list_links **links)
{
	t_list_rooms *current;
	t_list_links *lnks;

	current = *rms;
	while (current)
	{
		lnks = *links;
		current->num_lnks = 0;
		while (lnks)
		{
			if (ft_strequ(current->name, lnks->room1) ||
				ft_strequ(current->name, lnks->room2))
			{
				ft_lstaddnext(&(current->links), &lnks, sizeof(t_list_links));
				current->num_lnks++;
			}
			lnks = lnks->next;
		}
		current->act_lnks = current->num_lnks;
		current = current->next;
	}
}

static void	helper_cpy_the_rooms(t_list_rooms *s, t_list_rooms *d)
{
	d->status = s->status;
	d->num_lnks = s->num_lnks;
	d->x_cord = s->x_cord;
	d->y_cord = s->y_cord;
}

static void	cpy_the_rooms(t_list_rooms *s_rms, t_list_rooms **d_rms)
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
		helper_cpy_the_rooms(s, d);
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
		tmp = rms;
		d = (t_list_links *)ft_memalloc(sizeof(t_list_links));
		d->room1 = ft_strsub(s->room1, 0, ft_strlen(s->room1));
		d->room2 = ft_strsub(s->room2, 0, ft_strlen(s->room2));
		while (!ft_strequ(s->room1, tmp->name))
			tmp = tmp->next;
		d->rm1 = tmp;
		tmp = rms;
		while (!ft_strequ(s->room2, tmp->name))
			tmp = tmp->next;
		d->rm2 = tmp;
		d->sttus = s->sttus;
		d->way_nbr = s->way_nbr;
		d = d->next;
		s = s->next;
	}
}

void		cpy_the_state(t_intldta **inda, t_list_links **lnks,
		t_list_rooms **rms)
{
	cpy_the_rooms((*inda)->rooms, rms);
	cpy_the_links((*inda)->links, lnks, *rms);
	links_assignment(rms, lnks);
}
