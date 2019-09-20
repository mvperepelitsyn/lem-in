/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_search_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:22:28 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/13 19:22:30 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				not_in_searched(t_list_rooms *rm, t_search *searched,
		t_search *search)
{
	t_search *check;
	t_search *check2;

	check = searched;
	check2 = search;
	if (searched->rooms == NULL)
		return (1);
	else
	{
		while (check != NULL)
		{
			if (rm == check->rooms)
				return (0);
			check = check->next;
		}
		while (check2 != NULL)
		{
			if (rm == check2->rooms)
				return (0);
			check2 = check2->next;
		}
		return (1);
	}
}

void			free_search_ed(t_search **search, t_search **searched)
{
	if ((*search) != NULL)
	{
		while ((*search)->prev != NULL)
			*search = (*search)->prev;
		while ((*search)->next != NULL)
		{
			(*search) = (*search)->next;
			free((*search)->prev);
			(*search)->prev = NULL;
		}
		if ((*search)->prev != NULL)
		{
			free((*search)->prev);
			(*search)->prev = NULL;
		}
		free(*search);
		*search = NULL;
	}
	if (*searched != NULL)
		free_search_ed(searched, search);
}

static	void	help_fill_searched(t_search **s1, t_search **s2)
{
	if ((*s2)->step_nbr == 0)
	{
		(*s1)->rooms = (*s2)->rooms;
		(*s1)->way_nbr = (*s2)->way_nbr;
		(*s1)->step_nbr = (*s2)->step_nbr;
	}
	else
	{
		while ((*s1)->next != NULL)
			*s1 = (*s1)->next;
		(*s1)->next = (t_search *)ft_memalloc(sizeof(t_search));
		(*s1)->next->prev = *s1;
		(*s1)->next->rooms = (*s2)->rooms;
		(*s1)->next->way_nbr = (*s2)->way_nbr;
		(*s1)->next->step_nbr = (*s2)->step_nbr;
	}
}

void			fill_searched(t_search **searched, t_search **search)
{
	t_search	*s1;
	t_search	*s2;

	s1 = *searched;
	s2 = *search;
	help_fill_searched(&s1, &s2);
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
