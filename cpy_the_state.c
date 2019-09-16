/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_the_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:55:44 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/16 16:36:16 by dfrost-a         ###   ########.fr       */
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
		(*d_rms)->type = s->type;
		(*d_rms)->step_nbr = s->step_nbr;
		(*d_rms)->tmp_step_nbr = s->tmp_step_nbr;
		(*d_rms)->way_nbr = s->way_nbr;
//		(*d_rms)->prev = NULL;
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

static void	cpy_the_links(t_list_links *s_lnks, t_list_links **d_lnks,
		t_list_rooms *rms)
{
	t_list_links	*s;
	t_list_links	*d;
	t_list_rooms	*tmp;
	int 			cnt;
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

void		cpy_the_state(t_intldta **inda, t_list_links **lnks,
		t_list_rooms **rms)
{
	cpy_the_rooms((*inda)->rooms, rms);
	cpy_the_links((*inda)->links, lnks, *rms);
	links_assignment(rms, lnks);
}
