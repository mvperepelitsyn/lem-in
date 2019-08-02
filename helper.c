/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:35:41 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/08/02 19:40:02 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	help_fill_list_rooms(char **rms, t_list_rooms **current, short type)
{
	(*current)->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
	test_name((*current)->name);
	(*current)->x_cord = ft_latoi(rms[1]);
	(*current)->y_cord = ft_latoi(rms[2]);
	(*current)->type = type;
	if ((*current)->x_cord != ft_latoi(rms[1]) ||
	(*current)->y_cord != ft_latoi(rms[2]))
		ft_error();
//	test_coord((*current)->x_cord, (*current)->y_cord);
}

void	ft_malloc_error(void)
{
	ft_putstr("Malloc didn't allocate the memory\n");
	exit (73);
}

void 	ft_error(void)
{
	ft_putstr("ERROR\n");
	exit(69);
}

//void	test_coord(long int x, long int y)
//{
//	if ((x > 2147483647 || x < -2147483648) || (y > 2147483647 || y <
//	        -2147483648))
//		ft_error();
//}

void	test_double_room(const char *rm, t_intldta **indta)
{
	int ch;
	t_list_rooms *crt;

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

int 	test_links(t_list_links **links, t_intldta **indta) // i need the whole structure
{
	t_list_rooms *current;
	short check;

	current = (*indta)->rooms;
	check = 0;
	while (current)
	{
		if (ft_strequ((*links)->room1, current->name))
		{
			(*links)->rm1 = current;
			check++;
			break;
		}
		if (!(current = current->next))
			break;
	}
	current = (*indta)->rooms;
	while (current)
	{
		if (ft_strequ((*links)->room2, current->name))
			{
				(*links)->rm2 = current;
				check++;
				break;
			}
		if (!(current = current->next))
			break ;
	}
	return((check == 2) ? 1 : 0);
}

void	test_name(const char *name)
{
	if (*name == 'L' || *name == '#')
		ft_error();
}

void	ft_println(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

static void	print_rooms(t_intldta *indta)
{
	while (indta->rooms && indta->ri != -1)
	{
		ft_putstr(indta->rooms->name);
		ft_putstr(" ");
		ft_putnbr(indta->rooms->x_cord);
		ft_putstr(" ");
		ft_putnbr(indta->rooms->y_cord);
		ft_putstr("\n");
		indta->rooms = indta->rooms->next;
	}
}

void	print_links(t_list_links *links)
{
	while (links)
	{
		ft_putstr(links->room1);
		ft_putstr("-");
		ft_putstr(links->room2);
		ft_putstr("\n");
		links = links->next;
	}
}

void	print_sides(t_list_rooms *room)
{
	ft_putstr(room->name);
	ft_putstr(" ");
	ft_putnbr(room->x_cord);
	ft_putstr(" ");
	ft_putnbr(room->y_cord);
	ft_putstr("\n");
}

void	ft_print_strcut(t_intldta **indta)
{
	ft_putstr("The number of ants is ");
	ft_putnbr((*indta)->num_ants);
	ft_putchar('\n');
	ft_putstr("Here goes the rooms:\n");
	ft_putstr("Start room: ");
	print_sides((*indta)->start_room);
	ft_putstr("End room: ");
	print_sides((*indta)->end_room);
	ft_putstr("Other rooms:\n");
	print_rooms(*indta);
	ft_putstr("Here comes the links: \n");
	print_links((*indta)->links);
	ft_putstr("The end!\n");

}

void	init_struct(t_intldta **indta)
{
	if (!((*indta) = (t_intldta *)malloc(sizeof(t_intldta))))
		ft_malloc_error();
	(*indta)->start_room = NULL;
	(*indta)->end_room = NULL;
	(*indta)->rooms = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	(*indta)->links = (t_list_links *)malloc(sizeof(t_list_links));
	(*indta)->ri = -1;
	(*indta)->li = -1;
	(*indta)->links->next = NULL;
}

int 	check_double_link(t_list_links *links, char **rms)
{
	char *rm1;
	char *rm2;

	rm1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
	rm2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
	while (links)
	{
		if ((ft_strequ(rm1, links->room1) && ft_strequ(rm2, links->room2)) ||
		(ft_strequ(rm2, links->room1) && ft_strequ(rm1, links->room2)))
			return (1);
		links = links->next;
	}
	return (0);
}

void	free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
 		i++;
	}
	free(array);
	array = NULL;
}
