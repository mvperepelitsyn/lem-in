#include "lem_in.h"

static int lnks_assignmnt_help(t_list **t_lnks, t_list_links *ft_lnks, int *i)
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

static void	type_assignment(t_list_rooms *room, t_intldta **indta)
{
	if (room->type != 0)
	{
		if (room->type == 1)
			(*indta)->start_room = room;
		else
			(*indta)->end_room = room;
	}
}

void	fill_list_rooms(char **rms, t_intldta **indta, short type)
{
	t_list_rooms *current;

	current = (*indta)->rooms;
	if (++(*indta)->ri == 0)
	{
		help_fill_list_rooms(rms, &((*indta)->rooms), type);
		type_assignment((*indta)->rooms, indta);
		(*indta)->rooms->next = NULL;
		(*indta)->ri++;
		test_double_room((*indta)->rooms->name, indta);
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
		help_fill_list_rooms(rms, &(current->next), type);
		type_assignment(current->next, indta);
		current->next->next = NULL;
		test_double_room(current->next->name, indta);
	}
}

void	fill_list_links(t_list_links **links, char **rms, t_intldta **indta)
{
	t_list_links	*current;

	current = (*links);
	if (++(*indta)->li == 0)
	{
		(*links)->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		(*links)->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		if (!(test_links(links, indta)))
			ft_error();
		(*links)->next = NULL;
		(*indta)->li++;
		(*links)->status = 1;
		(*links)->way_nbr = -1;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		if (check_double_link(*links, rms))
			return ;
		current->next = (t_list_links *)malloc(sizeof(t_list_links));
		current->next->room1 = ft_strsub(rms[0], 0, ft_strlen(rms[0]));
		current->next->room2 = ft_strsub(rms[1], 0, ft_strlen(rms[1]));
		current->next->status = 1;
		current->next->way_nbr = -1;
		if (!(test_links(&current->next, indta)))
			ft_error();
		current->next->next = NULL;
	}
}

static void	parce_ant_farm(t_intldta **indta) //when we force it to read
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
	if ((*indta)->num_ants <= 0 || (*indta)->num_ants != (int)ft_latoi(things))
		ft_error();
	ft_strdel(&things);
    graph_parser(indta, &things, rms, fd);
	if ((*indta)->li == -1)
		ft_error();
	links_assignment(indta);
}

int		main(int argc, char **argv)
{
	t_intldta	*indta;

	init_struct(&indta);
	parce_ant_farm(&indta);
	if (argc == 2 && !ft_strcmp(argv[1], "-v"))
		indta->v_flag = 1;
	else
		indta->v_flag = 0;
	ft_putchar('\n');
//	print_all_the_links(indta->rooms);
	ft_print_strcut(&indta);
	ft_putchar('\n');
	find_the_way(indta);

	exit (0);
}
