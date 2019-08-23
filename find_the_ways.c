#include "find_way.h"

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
 	//TODO: It's needed to make an inisialisation for crnt_set and prev_set
 	if (!((*fnd_wy)->ways = (t_way *)malloc(sizeof(t_way))))
 		ft_malloc_error();
//	(*fnd_wy)->ways->rooms = ft_dllnew((void *)indta->start_room, 1);
//	(*fnd_wy)->ways->len_way = 0;
//	(*fnd_wy)->ways->num_way = 0;
//	(*fnd_wy)->ways->next = NULL;
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

static	void	add_to_searched(t_list_rooms **searched, t_list_rooms *end_room, int stp_nbr)
{
	t_list_rooms *srd;

	srd = *searched;
	while (srd->next != NULL)
		srd = srd->next;
	srd->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
	srd->next->prev = srd;
	cpy_t_list_room(srd->next, end_room);
	srd->next->step_nbr = stp_nbr + 1;
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
				add_to_searched(searched, pt_link->rm2, (*search)->step_nbr);
				return (0);
			}
			tmp->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
			cpy_t_list_room(tmp->next, pt_link->rm2);
			tmp->next->prev = tmp;
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
				add_to_searched(searched, pt_link->rm1, (*search)->step_nbr);
				return (0);
			}
			tmp->next = (t_list_rooms *)malloc(sizeof(t_list_rooms));
			tmp->next->prev = tmp;
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
		s1->next->prev = s1;
		cpy_t_list_room(s1->next, s2);
	}
	if ((*search)->next != NULL)
	{
		*search = (*search)->next;
		free(s2);
		s2 = NULL;
	}
}

//static int	fill_the_way_help(t_dllist **rooms, t_list_rooms *ft_room, int cnt)
//{
//	t_dllist	*add_way;
//
//	add_way = *rooms;
//	if (ft_room->step_nbr == 0)
//	{
//		add_way = ft_dllnew(void const *content, size_t content_size)ft_lstnew_addr((void *)ft_room, ft_room->step_nbr + 1);
//		return (0);
//	}
//	else
//	{
//		while (add_way->next != NULL)
//			add_way = add_way->next;
//		add_way->next = ft_lstnew_addr((void *)ft_room, ft_room->step_nbr);
//		return (0);
//	}
//}


static	int 	it_has_link(t_list_rooms *room1, t_list_rooms *room2)
{
	t_list			*ptr1;
	t_list_links	*lnks;
	t_list_rooms	*rm_1;

	rm_1 = room1;
	ptr1 = rm_1->links;
	while (ptr1)
	{
		lnks = ptr1->content;
		if ((ft_strequ(rm_1->name, lnks->room1) && ft_strequ(room2->name,
				lnks->room2)) || (ft_strequ(room2->name, lnks->room1) &&
				ft_strequ(rm_1->name, lnks->room2)))
			return (1);
		ptr1 = ptr1->next;
	}
	return (0);
}

static	void	del_t_list_room(t_list_rooms **room)
{
	t_list_rooms *tmp;

	tmp = *room;
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	ft_strdel(&tmp->name);
	free(tmp);
}

static	void	make_it_clean(t_list_rooms **lst_rooms)
{
	t_list_rooms	*tmp;
	t_list_rooms	*tmp2;
	int				cnt;

	tmp = *lst_rooms;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp = tmp->prev;
	while (tmp->prev != NULL)
	{
		cnt = 0;
		if ((tmp->step_nbr >= tmp->next->step_nbr) || !it_has_link(tmp,
				tmp->next) || !it_has_link(tmp, tmp->prev))
		{
			if (!it_has_link(tmp, tmp->prev) && tmp->step_nbr < tmp->next->step_nbr)
			{
				tmp2 = tmp->prev;
				while (tmp2->prev != NULL)
				{
					if (it_has_link(tmp, tmp2) && tmp2->step_nbr < tmp->step_nbr)
					{
						cnt = 1;
						tmp2 = tmp2->next;
						while (!ft_strequ(tmp2->name, tmp->name))
						{
							del_t_list_room(&tmp2);
							tmp2 = tmp2->next;
						}
						break ;
					}
					tmp2 = tmp2->prev;
				}
				if (tmp2->prev == NULL)
				{
					if (it_has_link(tmp, tmp2) && tmp2->step_nbr < tmp->step_nbr)
					{
						cnt = 1;
						tmp2 = tmp2->next;
						while (!ft_strequ(tmp2->name, tmp->name))
						{
							del_t_list_room(&tmp2);
							tmp2 = tmp2->next;
						}
						break ;
					}
					tmp2 = tmp2->prev;
				}
			}
			if (cnt == 0)
				del_t_list_room(&tmp);
		}
		tmp = tmp->prev;
	}
}

static	void	fill_the_way(t_find_way **fnd_way, t_list_rooms *list)
{
	t_find_way *add_way;
	int 		cnt;
	int 		spin;
//	t_list_rooms	*ptr;

	add_way = *fnd_way;
	make_it_clean(&list);
	add_way->ways->rooms = ft_dllnew((void *) list, sizeof(t_list_rooms));
	list = list->next;
	while (list->next != NULL)
	{
		ft_dlladdnextr(&(add_way->ways->rooms), (void *) list,
				sizeof(t_list_rooms));
		list = list->next;
	}
	ft_dlladdnextr(&(add_way->ways->rooms), (void *) list, sizeof(t_list_rooms));
	add_way->ways->len_way = list->step_nbr;
	ft_printf("\nLength of the way = %d\n", add_way->ways->len_way);
//	cnt = list->step_nbr - 1;
//	spin = 0;
//	list = list->prev;
//	while (list)
//	{
////		ptr = add_way->ways->rooms->content;
//		if (cnt == list->step_nbr)
//		{
//			if (it_has_link((t_list_rooms *)add_way->ways->rooms->content, list))
//			{
//				ft_dlladdnextr(&(add_way->ways->rooms), (void *) list,
//						sizeof(t_list_rooms));
//				spin++;
//				cnt--;
//			}
//			else
//				spin++;
//			list = list->prev;
//		}
//		else
//			list = list->prev;
//	}
}

static	void	print_the_way(t_way *way)
{
	t_dllist		*ptr;
	t_list_rooms	*ptr2;

	ptr = way->rooms;
	while (ptr != NULL)
	{
		ptr2 = ptr->content;
		if (ptr->right != NULL)
			ft_printf("%s->", ptr2->name);
		else
			ft_printf("%s", ptr2->name);
		ptr = ptr->right;
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
	search->prev = NULL;
	searched->prev = NULL;
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
 	print_all_the_links(indta->rooms);
// 	exit (69);
// 	fill_the_way(&fnd_wy, indta);
// 	print_the_way();
 	return (0);
}
