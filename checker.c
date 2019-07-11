/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:04:14 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/11 18:22:03 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	fill_list_rooms(t_list_rooms **rooms, char **rms)
{
	t_list_rooms *current;

	current = (*rooms);
	if ((*rooms)->i == 0)
	{
		(*rooms)->room = (t_room *)malloc(sizeof(t_room));
		(*rooms)->room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*rooms)->room->x_cord = ft_atoi(rms[1]);
		(*rooms)->room->y_cord = ft_atoi(rms[2]);
		(*rooms)->next = NULL;
		(*rooms)->i++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
		current->next->room = (t_room *)malloc(sizeof(t_room));
		current->next->room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		current->next->room->x_cord = ft_atoi(rms[1]);
		current->next->room->y_cord = ft_atoi(rms[2]);
		current->next->next = NULL;
	}
}

void	fill_list_links(t_list_links **links, char **rms)
{
	t_list_links	*current;

	current = (*links);
	if ((*links)->i == 0)
	{
		(*links)->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*links)->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		(*links)->next = NULL;
		(*links)->i++;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_links *)malloc(sizeof(t_list_links));
		current->next->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		current->next->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		current->next->next = NULL;
	}
}

void	parce_ant_farm(t_test *test, int argc, char **argv)
{
	char *things;
	char **rms;

	get_next_line(0, &things);
	test->num_ants = ft_atoi(things);
	ft_strdel(&things);
	test->rooms = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	test->links = (t_list_links *)malloc(sizeof(t_list_links));
	test->rooms->i = 0;
	test->links->i = 0;
	test->links->next = NULL;
	while (get_next_line(0, &things))
	{
		if (ft_strequ("##start", things))
		{
			get_next_line(0, &things);
			rms = ft_strsplit(things, ' ');
			test->start_room = (t_room *)malloc(sizeof(t_room));
			test->start_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test->start_room->x_cord = ft_atoi(rms[1]);
			test->start_room->y_cord = ft_atoi(rms[2]);
		}
		else if (ft_strequ("##end", things))
		{
			get_next_line(0, &things);
			rms = ft_strsplit(things, ' ');
			test->end_room = (t_room *)malloc(sizeof(t_room));
			test->end_room->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
			test->end_room->x_cord = ft_atoi(rms[1]);
			test->end_room->y_cord = ft_atoi(rms[2]);
		}
		else if (ft_hm_wrd(things, ' ') == 3)
		{
			rms = ft_strsplit(things, ' ');
			fill_list_rooms(&test->rooms, rms);
		}
		else if (ft_hm_wrd(things, '-'))
		{
			rms = ft_strsplit(things, '-');
			fill_list_links(&test->links, rms);
		}
		ft_strdel(&things);
	}
}

//void	do_cmd(t_stack *stack)
//{
//	char *cmd;
//
//	while (get_next_line(0, &cmd))
//	{
//		if (!cmd)
//			break ;
//		if (get_cmd(stack, cmd))
//			break ;
//		free(cmd);
//		cmd = NULL;
//	}
//	free(cmd);
//}

int		main(int argc, char **argv)
{
	t_test	*test;

	if (!(test = (t_test *)malloc(sizeof(t_test))))
		ft_malloc_error();
	parce_ant_farm(test, argc, argv);
	exit (69);
//	do_cmd(stack);
//	if (!(is_ok(stack)))
//	{
//		ft_putstr("KO\n");
//		exit(13);
//	}
//	return (0);
}
