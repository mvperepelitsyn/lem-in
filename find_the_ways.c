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

static	void	fill_search(t_list_rooms **search, t_list_rooms *searched)
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
				pt_link->room2, searched, *search)))
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
			cpy_t_list_room(tmp->next, pt_link->rm2);
			tmp->next->step_nbr = (*search)->step_nbr + 1;
		}
		else if (ft_strequ(pt_link->room2, (*search)->name) && not_in_searched(
				pt_link->room1, searched, *search))
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			tmp->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
			cpy_t_list_room(tmp->next, pt_link->rm1);
			tmp->next->step_nbr = (*search)->step_nbr + 1;
		}
		ptr = ptr->next;
		act_lnks--;
	}
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

static	void	fill_searched(t_list_rooms **searched, t_list_rooms **search)
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
		if (what_status(s_lnks, s2->name))
			;
		else
		{
			while (s1->next != NULL)
				s1 = s1->next;
			s1->next = (t_list_rooms *) malloc(sizeof(t_list_rooms));
			cpy_t_list_room(s1->next, s2);
		}
	}
	*search = (*search)->next;
	free(s2);
	s2 = NULL;
}

//static	int 	is_it_end()

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
		{
			fill_search(&search, searched);
			fill_searched(&searched, &search);
		}
	}
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
