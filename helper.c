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
	(*current)->name = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
	test_name((*current)->name);
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

void	init_struct(t_intldta **indta)
{
	if (!((*indta) = (t_intldta *)ft_memalloc(sizeof(t_intldta))))
		ft_malloc_error();
	(*indta)->start_room = NULL;
	(*indta)->end_room = NULL;
	(*indta)->rooms = (t_list_rooms *)ft_memalloc(sizeof(t_list_rooms));
	(*indta)->links = (t_list_links *)ft_memalloc(sizeof(t_list_links));
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
	if (ft_strequ(rm1, rm2))
	{
		ft_strdel(&rm1);
		ft_strdel(&rm2);
		return (1);
	}
	while (links)
	{
		if ((ft_strequ(rm1, links->room1) && ft_strequ(rm2, links->room2)) ||
		(ft_strequ(rm2, links->room1) && ft_strequ(rm1, links->room2)))
		{
			ft_strdel(&rm1);
			ft_strdel(&rm2);
			return (1);
		}
		links = links->next;
	}
	ft_strdel(&rm1);
	ft_strdel(&rm2);
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
