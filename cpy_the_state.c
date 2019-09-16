/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_the_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:23:08 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/16 17:23:23 by dfrost-a         ###   ########.fr       */
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

void		cpy_the_state(t_intldta **inda, t_list_links **lnks,
		t_list_rooms **rms)
{
	cpy_the_rooms((*inda)->rooms, rms);
	cpy_the_links((*inda)->links, lnks, *rms);
	links_assignment(rms, lnks);
}
