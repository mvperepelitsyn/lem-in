/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_search_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 20:53:30 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/18 11:13:26 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	cpy_helper(t_search **tmp_l, t_search **tmp_d)
{
	(*tmp_l)->rooms = (*tmp_d)->rooms;
	(*tmp_l)->step_nbr = (*tmp_d)->step_nbr;
	(*tmp_l)->way_nbr = (*tmp_d)->way_nbr;
	(*tmp_l)->next = (t_search *)ft_memalloc(sizeof(t_search));
	(*tmp_l)->next->prev = (*tmp_l);
	(*tmp_l) = (*tmp_l)->next;
	(*tmp_d) = (*tmp_d)->next;
}

static void	cpy_t_searched(t_search **srchd, t_search **lst, t_list_links
*end_lnk)
{
	t_search *tmp_l;
	t_search *tmp_d;

	*lst = (t_search *)ft_memalloc(sizeof(t_search));
	tmp_l = *lst;
	tmp_d = *srchd;
	while (tmp_d && tmp_d->rooms != NULL)
		cpy_helper(&tmp_l, &tmp_d);
	tmp_l->rooms = (end_lnk->rm2->type == 2) ? end_lnk->rm1 : end_lnk->rm2;
	tmp_l->step_nbr = tmp_l->rooms->tmp_step_nbr;
	if (tmp_l->prev)
		tmp_l->way_nbr = tmp_l->prev->way_nbr;
	else
		tmp_l->way_nbr = 1;
	tmp_l->next = (t_search *)ft_memalloc(sizeof(t_search));
	tmp_l->next->prev = tmp_l;
	tmp_l = tmp_l->next;
	tmp_l->rooms = (end_lnk->rm2->type == 2) ? end_lnk->rm2 : end_lnk->rm1;
	tmp_l->step_nbr = tmp_l->prev->step_nbr + 1;
	tmp_l->way_nbr = tmp_l->prev->way_nbr;
	make_it_clean(&tmp_l);
}

static void	change_the_way_nbr(t_search **srch, t_search **srchd, int way_nbr)
{
	t_search *s1;
	t_search *s2;

	s1 = *srch;
	s2 = *srchd;
	while (s1)
	{
		if (s1->way_nbr > 0)
			s1->way_nbr = way_nbr;
		s1 = s1->next;
	}
	while (s2)
	{
		if (s2->way_nbr > 0)
			s2->way_nbr = way_nbr;
		s2 = s2->next;
	}
}

static int	check_the_way(t_search *lst)
{
	t_search *tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->rooms->way_nbr > 0)
			return (1);
		if (tmp->next && !it_has_link(tmp->rooms, tmp->next->rooms))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		add_the_way(t_find_way **fnd, t_search **srch, t_search **srchd,
		t_list_links *end_lnk)
{
	t_way		*way;
	t_search	*lst;
	t_search	*trash;
	int			check;

	trash = NULL;
	cpy_t_searched(srchd, &lst, end_lnk);
	if (check_the_way(lst))
	{
		free_search_ed(&lst, &trash);
		return ;
	}
	check = give_me_way_nbr(&((*fnd)->ways));
	way = (t_way *)ft_memalloc(sizeof(t_way));
	way->status = 1;
	way->num_way = check;
	fill_the_way(&way, lst);
	free_search_ed(&lst, &trash);
	insert_way(*fnd, way);
	(*fnd)->cnt_ways++;
	change_the_way_nbr(srch, srchd, give_me_way_nbr(&((*fnd)->ways)));
}
