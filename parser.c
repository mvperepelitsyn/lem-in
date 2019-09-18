/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <dfrost-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:36:23 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/18 17:37:49 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	links_assignment(t_intldta **indta)
{
	t_list_rooms *current;
	t_list_links *lnks;

	current = (*indta)->rooms;
	while (current)
	{
		lnks = (*indta)->links;
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

static void	parce_ant_farm(t_intldta **indta)
{
	char	*things;
	char	**rms;
	int		fd;

	fd = 0;
	get_next_line(fd, &things);
	(things == NULL) ? ft_error() : ft_println(things);
	while (things && (things[0] == '#' && things[1] != '#'))
	{
		ft_strdel(&things);
		get_next_line(fd, &things);
		if (things)
			ft_println(things);
	}
	(*indta)->num_ants = ft_latoi(things);
	if (ft_hm_wrd(things, ' ') != 1 || ((*indta)->num_ants <= 0 || (*indta)->
	num_ants != (long long int)ft_latoi(things)))
		ft_error();
	ft_strdel(&things);
	rms = NULL;
	graph_parser(indta, &things, rms, fd);
	if ((*indta)->li == -1)
		ft_error();
	links_assignment(indta);
}

int			main(int ac, char **av)
{
	t_intldta	*indta;

	init_struct(&indta);
	parce_ant_farm(&indta);
	if (ac == 2 || ac == 3)
	{
		if (!ft_strcmp(av[1], "-v") || (ac == 3 && !ft_strcmp(av[2], "-v")))
			indta->v_flag = 1;
		if (!ft_strcmp(av[1], "-r") || (ac == 3 && !ft_strcmp(av[2], "-r")))
			indta->r_flag = 1;
	}
	ft_putchar('\n');
	find_the_way(indta);
	exit(0);
}
