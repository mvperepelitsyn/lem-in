/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 14:36:23 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/13 14:59:54 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	lnks_assignmnt_help(t_list **t_lnks, t_list_links *ft_lnks, int *i)
{
	t_list *lnks;

	lnks = (*t_lnks);
	if (*i == 0)
	{
		(*t_lnks) = ft_lstnew_addr((void *)ft_lnks, ++*i);
		return (0);
	}
	while ((*t_lnks)->next != NULL)
		*t_lnks = (*t_lnks)->next;
	(*t_lnks)->next = ft_lstnew_addr((void *)ft_lnks, ++*i);
	(*t_lnks) = lnks;
	return (0);
}

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
				lnks_assignmnt_help(&current->links, lnks, &current->num_lnks);
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

	if ((fd = open(NAME, O_RDONLY)) < 0)
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
	num_ants != (int)ft_latoi(things)))
		ft_error();
	ft_strdel(&things);
	rms = NULL;
	graph_parser(indta, &things, rms, fd);
	if ((*indta)->li == -1)
		ft_error();
	links_assignment(indta);
}

int			main(int argc, char **argv)
{
	t_intldta	*indta;

	init_struct(&indta);
	parce_ant_farm(&indta);
	if (argc == 2 && !ft_strcmp(argv[1], "-v"))
		indta->v_flag = 1;
	else
		indta->v_flag = 0;
	ft_putchar('\n');
	ft_putchar('\n');
	find_the_way(indta);
	exit(0);
}
