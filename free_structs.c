/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:52:27 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/15 16:54:31 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_t_ways(t_way **ways)
{
	t_way *tmp_way;

	while (*ways)
	{
		ft_dlldeltoright(&((*ways)->rooms), &ft_lstfree);
		tmp_way = (*ways)->next;
		free(*ways);
		*ways = NULL;
		*ways = tmp_way;
	}
}

static void	free_t_sets(t_way_set **sets)
{
	t_way_set *tmp_set;

	while (*sets)
	{
		ft_lstdel(&((*sets)->ways), &ft_lstfree);
		tmp_set = (*sets)->next;
		(*sets)->next = NULL;
		free(*sets);
		*sets = NULL;
		*sets = tmp_set;
	}
}

static void	free_find_way(t_find_way **find)
{
	free_t_ways(&((*find)->ways));
	free_t_sets(&((*find)->sets));
	free(*find);
	*find = NULL;
}

void		free_main_structs(t_intldta **intldta, t_find_way **find)
{
	free_indta(intldta);
	free_find_way(find);
}
