#include "find_way.h"

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
 	//TODO: It's needed to make an inisialisation for crnt_set and prev_set
 	if (!((*fnd_wy)->ways = (t_way *)malloc(sizeof(t_way))))
 		ft_malloc_error();
	(*fnd_wy)->ways->rooms = ft_lstnew_addr((void *)indta->start_room, 0);
	(*fnd_wy)->ways->rooms->next = NULL;
	(*fnd_wy)->ways->len_way = 0;
	(*fnd_wy)->ways->num_way = 0;
	(*fnd_wy)->ways->next = NULL;
	(*fnd_wy)->start = indta->start_room;
	 if (!((*fnd_wy)->crnt_set = (t_way_set *)malloc(sizeof(t_way_set))))
	 	ft_malloc_error();
	(*fnd_wy)->crnt_set->steps = 0;
	(*fnd_wy)->crnt_set->ways_cnt = 0;
	(*fnd_wy)->way_nbr = 0;
}

//static void	copy_the_way(t_way *way)
//{
// 	ft_putstr("This is the way:\n");
// 	ft_putstr(way->room);
// 	way = way->next;
// 	while (way)
// 	{
// 		ft_putstr("->");
// 		ft_putstr(way->room);
// 		way = way->next;
// 	}
//}

//void	fill_the_way(t_find_way **fnd_wy, t_intldta *indta)
//{
// 	t_ways				*f_ways;
// 	t_list_rooms		*ptr;
//
// 	f_ways = (*fnd_wy)->crnt_set->ways;
// 	f_ways->way->rooms = (*fnd_wy)->shortest_way->rooms;
// 	while (1)
//	{
// 		while (f_ways->way->rooms->act_lnks != 0)
//
//	}
//
//
//}

static	int 	not_in_searched(char *room, t_list_rooms *searched, t_list_rooms *search)
{
	t_list_rooms *check;
	t_list_rooms *check2;

	check = searched;
	check2 = search;
	if (searched->name == NULL)
		return (1);
	else
	{
		while (check != NULL)
		{
			if (ft_strequ(room, check->name))
				return (0);
			check = check->next;
		}
		while (check2 != NULL)
		{
			if (ft_strequ(room, check2->name))
				return (0);
			check2 = check2->next;
		}
		return (1);
	}
}

static	void	add_to_searched(t_list_rooms **searched, t_list_rooms *end_room)
{
	t_list_rooms *srd;

	srd = *searched;
	while (srd->next != NULL)
		srd = srd->next;
	srd->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	cpy_t_list_room(srd->next, end_room);
}

static	int	fill_search(t_list_rooms **search, t_list_rooms **searched)
{
	t_list_rooms	*tmp;
	int 			act_lnks;
	t_list			*ptr;
	t_list_links	*pt_link;

	act_lnks = (*search)->act_lnks;
	ptr = (*search)->links;
	while (act_lnks != 0 || ptr != NULL)
	{
		tmp = *search;
		pt_link = ptr->content;
		if ((ft_strequ(pt_link->room1, (*search)->name) && not_in_searched(
				pt_link->room2, *searched, *search)))
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			if (pt_link->rm2->type == 2)
			{
				fill_searched(searched, search);
				add_to_searched(searched, pt_link->rm2);
				return (0);
			}
			tmp->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
			cpy_t_list_room(tmp->next, pt_link->rm2);
			tmp->next->step_nbr = (*search)->step_nbr + 1;
		}
		else if (ft_strequ(pt_link->room2, (*search)->name) && not_in_searched(
				pt_link->room1, *searched, *search))
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			if (pt_link->rm1->type == 2)
			{
				fill_searched(searched, search);
				add_to_searched(searched, pt_link->rm1);
				return (0);
			}
			tmp->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
			cpy_t_list_room(tmp->next, pt_link->rm1);
			tmp->next->step_nbr = (*search)->step_nbr + 1;
		}
		ptr = ptr->next;
		act_lnks--;
	}
	return (1);
}

static	int 	what_status(t_list *lnks, char *room)
{
	t_list			*ptr;
	t_list_links 	*st_lnks;

	ptr = lnks;
	while (ptr != NULL)
	{
		st_lnks = ptr->content;
		if ((ft_strequ(room, st_lnks->room1) && st_lnks->rm2->status == 0) ||
		(ft_strequ(room, st_lnks->room2) && st_lnks->rm1->status == 0))
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void			fill_searched(t_list_rooms **searched, t_list_rooms **search)
{
	t_list_rooms	*s1;
	t_list_rooms	*s2;
	t_list			*s_lnks;
//TODO: IF ALL THE ROOMS IN LINKS OF THE ROOM THAT WE WANT TO ADD HAVE STATUS 1 THEN WE DO NOT ADD IT TO THE LIST OF SEARCHED
	s1 = *searched;
	s2 = *search;
	s_lnks = s2->links;
	if ((*search)->step_nbr == 0)
		cpy_t_list_room(s1, s2);
	else
	{
		while (s1->next != NULL)
			s1 = s1->next;
		s1->next = (t_list_rooms *) malloc(sizeof(t_list_rooms));
		cpy_t_list_room(s1->next, s2);
	}
	*search = (*search)->next;
	free(s2);
	s2 = NULL;
}

static int	fill_the_way_help(t_list **rooms, t_list_rooms *ft_room, int cnt)
{
	t_list	*add_way;

	add_way = *rooms;
	if (ft_room->step_nbr == 0)
	{
		add_way = ft_lstnew_addr((void *)ft_room, ft_room->step_nbr + 1);
		return (0);
	}
	else
	{
		while (add_way->next != NULL)
			add_way = add_way->next;
		add_way->next = ft_lstnew_addr((void *)ft_room, ft_room->step_nbr);
		return (0);
	}
}

static	void	fill_the_way(t_find_way **fnd_way, t_list_rooms *list)
{
	t_find_way *add_way;
	int 		cnt;

	add_way = *fnd_way;
	cnt = 0;
	while (list != NULL)
	{
		if (list->step_nbr == cnt)
		{
			fill_the_way_help(&(add_way->ways->rooms), list, cnt);
			add_way->ways->len_way = cnt;
			cnt++;
		}
		else
			list = list->next;
	}
}

static	void	print_the_way(t_way *way)
{
	t_list			*ptr;
	t_list_rooms	*ptr2;

	ptr = way->rooms;
	while (ptr != NULL)
	{
		ptr2 = ptr->content;
		ft_printf("%s->", ptr2->name);
		ptr = ptr->next;
	}
	ft_putstr("\n");
}

static	int		wide_search(t_find_way **fnd_way, t_intldta *indta)
{
	t_list_rooms	*search;
	t_list_rooms	*searched;

	search = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	searched = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	searched->name = NULL;
	cpy_t_list_room(search, indta->start_room);
	search->next = NULL;
	search->step_nbr = 0;
	while (!ft_strequ(search->name, indta->end_room->name))
	{
		if (ft_strequ(search->name, indta->end_room->name))
			break ;
		else
			if (fill_search(&search, &searched))
				fill_searched(&searched, &search);
			else
				break ;
	}
	fill_the_way(fnd_way, searched);
	print_the_way((*fnd_way)->ways);
}

void	cpy_t_list_room(t_list_rooms *dest, t_list_rooms *src)
{
	dest->step_nbr = src->step_nbr;
	dest->links = src->links;
	dest->act_lnks = src->act_lnks;
	dest->name = ft_strsub(src->name, 0, ft_strlen(src->name));
	src->status = 1;
	dest->status = src->status;
	dest->type = src->type;
	dest->x_cord = src->x_cord;
	dest->y_cord = src->y_cord;
	dest->num_lnks = src->num_lnks;
	dest->way_nbr = src->way_nbr;
	dest->next = NULL;
}

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*fnd_wy;

 	init_set(&fnd_wy, indta);
 	wide_search(&fnd_wy, indta);
// 	exit (69);
// 	fill_the_way(&fnd_wy, indta);
// 	print_the_way();
 	return (0);
}
