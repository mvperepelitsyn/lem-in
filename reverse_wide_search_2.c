/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_wide_search_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:36:16 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/13 21:36:19 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	rev_help_fill_searched(t_search **s1, t_search **s2)
{
	if ((*s2)->step_nbr == 0)
	{
		(*s1)->rooms = (*s2)->rooms;
		(*s1)->step_nbr = (*s2)->step_nbr;
	}
	else
	{
		while ((*s1)->next != NULL)
			*s1 = (*s1)->next;
		(*s1)->next = (t_search *)ft_memalloc(sizeof(t_search));
		(*s1)->next->prev = *s1;
		(*s1)->next->rooms = (*s2)->rooms;
		(*s1)->next->step_nbr = (*s2)->step_nbr;
	}
}

void			rev_fill_searched(t_search **searched, t_search **search)
{
	t_search	*s1;
	t_search	*s2;

	s1 = *searched;
	s2 = *search;
	rev_help_fill_searched(&s1, &s2);
	if ((*search)->next != NULL)
	{
		*search = (*search)->next;
		free(s2);
		s2 = NULL;
		(*search)->prev = NULL;
	}
	else
	{
		free(*search);
		*search = NULL;
	}
}
