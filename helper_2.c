/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:13:35 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/09/18 15:30:24 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	erase_tmp_step_nbr(t_list_rooms *rooms)
{
	t_list_rooms *tmp;

	tmp = rooms;
	while (tmp)
	{
		tmp->tmp_step_nbr = (tmp->way_nbr < 0) ? 0 : tmp->tmp_step_nbr;
		tmp = tmp->next;
	}
}

void	help_fill_list_rooms(char **rms, t_list_rooms **current, short type)
{
	char *check;

	check = rms[0];
	while (*check)
	{
		if (*check == '-')
			ft_error();
		check++;
	}
	(*current)->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
	if ((*current)->name[0] == 'L' || (*current)->name[0] == '#')
		ft_error();
	(*current)->x_cord = ft_latoi(rms[1]);
	(*current)->y_cord = ft_latoi(rms[2]);
	(*current)->type = type;
	if ((*current)->x_cord != ft_latoi(rms[1]) ||
		(*current)->y_cord != ft_latoi(rms[2]))
		ft_error();
	(*current)->links = NULL;
	(*current)->way_nbr = -1;
	(*current)->step_nbr = -1;
	(*current)->status = 0;
}

void	ft_malloc_error(char *str)
{
	if (!str)
		ft_putstr("Malloc didn't allocate the memory\n");
	else
		ft_printf("%s\n", str);
	exit(73);
}

void	ft_error(void)
{
	ft_putstr("ERROR\n");
	exit(69);
}

void	test_double_room(const char *rm, t_intldta **indta)
{
	int				ch;
	t_list_rooms	*crt;

	ch = 0;
	crt = (*indta)->rooms;
	while (crt)
	{
		if (ft_strequ(rm, crt->name))
			ch++;
		if (crt->next == NULL)
			break ;
		else
			crt = crt->next;
	}
	if (ch != 1)
		ft_error();
}
