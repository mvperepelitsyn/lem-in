#include "lem_in.h"

static	void	del_t_way(t_way **way)
{
	*way = (*way)->prev;
	free((*way)->next);
	(*way)->next = NULL;
}

static	void	free_search_ed(t_search **search, t_search **searched)
{
	if ((*search) != NULL)
	{
		while ((*search)->prev != NULL)
			*search = (*search)->prev;
		while ((*search)->next != NULL)
		{
			(*search) = (*search)->next;
			free((*search)->prev);
			(*search)->prev = NULL;
		}
		if ((*search)->prev != NULL)
		{
			free((*search)->prev);
			(*search)->prev = NULL;
		}
		free(*search);
		*search = NULL;
	}
	if (*searched != NULL)
		free_search_ed(searched, search);

}

void		remove_way_nbr(t_way **ways)
{
	t_way			*tmp_way;
	t_dllist		*tmp_room;
	t_list_rooms	*tmp;

	tmp_way = *ways;
	ft_printf("\nLength of the way = %d\n", tmp_way->len_way);
	while (tmp_way)
	{
		tmp_room = tmp_way->rooms;
		while (tmp_room)
		{
			tmp = tmp_room->content;
			if (tmp->way_nbr > 0)
				tmp->way_nbr = -1;
			tmp_room = tmp_room->right;
		}
		tmp_way = tmp_way->next;
	}
}

static	void	print_the_way(t_way **way)
{
	t_dllist		*ptr;
	t_list_rooms	**ptr2;

	ptr = (*way)->rooms;
	ft_putstr("\n");
	while (ptr != NULL)
	{
		ptr2 = ptr->content;
		if (ptr->right != NULL)
			ft_printf("%s->", (*ptr2)->name);
		else
			ft_printf("%s", (*ptr2)->name);
		ptr = ptr->right;
	}
	ft_putstr("\n");
}

void		print_the_answer(t_way_set	*answer)
{
	t_list	*list_ways;

	list_ways = answer->ways;
	ft_printf("Here is a set of ways, that would be the best for our ant-farm:");
	while (list_ways)
	{
		print_the_way((t_way **)(list_ways->content));
		list_ways = list_ways->next;
	}
}

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)malloc(sizeof(t_find_way))))
 		ft_malloc_error();
 	//TODO: It's needed to make an inisialisation for crnt_set and prev_set
// 	if (!((*fnd_wy)->ways = (t_way *)malloc(sizeof(t_way))))
// 		ft_malloc_error();
	(*fnd_wy)->ways = NULL;
	(*fnd_wy)->start = indta->start_room;
	(*fnd_wy)->sets = NULL;
	(*fnd_wy)->crnt_set = NULL;
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

static	int 	not_in_searched(char *room, t_search *searched, t_search *search)
{
	t_search *check;
	t_search *check2;

	check = searched;
	check2 = search;
	if (searched->rooms == NULL)
		return (1);
	else
	{
		while (check != NULL)
		{
			if (ft_strequ(room, check->rooms->name))
				return (0);
			check = check->next;
		}
		while (check2 != NULL)
		{
			if (ft_strequ(room, check2->rooms->name))
				return (0);
			check2 = check2->next;
		}
		return (1);
	}
}

static	void	add_to_searched(t_search **searched, t_list_rooms *end_room, int stp_nbr)
{
	t_search *srd;

	srd = *searched;
	while (srd->next != NULL)
		srd = srd->next;
	srd->next = (t_search *)ft_memalloc(sizeof(t_search));
	srd->next->prev = srd;
	srd->next->rooms = end_room;
	srd->next->way_nbr = -1;
	srd->next->step_nbr = stp_nbr + 1;
}

static	int stop_search(t_find_way **find, t_list_links *links, t_list_rooms *room)
{
	t_list_links *lnks;

	lnks = links;
	while (lnks)
	{
		if (ft_strequ(lnks->room1, room->name) && lnks->rm2->way_nbr > 0 && lnks->status == 1 && lnks->way_nbr < 0)
		{
			if (link_breaker(find, lnks->rm2))
				return (1);
			else
			{
				lnks->status = 0;
				lnks->rm1->act_lnks--;
				lnks->rm2->act_lnks--;
			}
		}
		else if (ft_strequ(lnks->room2, room->name) && lnks->rm1->way_nbr > 0 && lnks->status == 1 && lnks->way_nbr < 0)
		{
			if (link_breaker(find, lnks->rm1))
				return (1);
			else
			{
				lnks->status = 0;
				lnks->rm1->act_lnks--;
				lnks->rm2->act_lnks--;
			}
		}
		lnks = lnks->next;
	}
	return (0);
}

static	int	fill_search(t_find_way **find, t_search **search, t_search **searched)
{
	t_search		*tmp;
	int 			num_lnks;
	t_list			*ptr;
	t_list_links	*pt_link;
	t_search		*ftmp;

	num_lnks = (*search)->rooms->num_lnks;
	ptr = (*search)->rooms->links;
	ftmp = *search;
	while (ftmp->next != NULL)
		ftmp = ftmp->next;
	while (num_lnks != 0 || ptr != NULL)
	{
		tmp = *search;
		pt_link = ptr->content;
		if (stop_search(find, pt_link, tmp->rooms)) //search in links that have links with that room todo list
			return (0);
		if (ft_strequ(pt_link->room1, (*search)->rooms->name) && not_in_searched(
				pt_link->room2, *searched, *search)  && pt_link->rm2->way_nbr <
				        0 && pt_link->status == 1)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			if (pt_link->rm2->type == 2)
			{
				fill_searched(searched, search);
				add_to_searched(searched, pt_link->rm2, (*search)->step_nbr);
				return (0);
			}
			tmp->next = (t_search *)ft_memalloc(sizeof(t_search));
			tmp->next->rooms = pt_link->rm2;
			tmp->next->way_nbr = tmp->way_nbr;
			tmp->next->prev = tmp;
			tmp->next->step_nbr = (*search)->step_nbr + 1;
		}
		else if (ft_strequ(pt_link->room2, (*search)->rooms->name) && not_in_searched(
				pt_link->room1, *searched, *search) && pt_link->rm1->way_nbr < 0
				&& pt_link->status == 1)
		{
			while (tmp->next != NULL)
				tmp = tmp->next;
			if (pt_link->rm1->type == 2)
			{
				fill_searched(searched, search);
				add_to_searched(searched, pt_link->rm1, (*search)->step_nbr);
				return (0);
			}
			tmp->next = (t_search *)ft_memalloc(sizeof(t_search));
			tmp->next->prev = tmp;
			tmp->next->rooms = pt_link->rm1;
			tmp->next->way_nbr = tmp->way_nbr;
			tmp->next->step_nbr = (*search)->step_nbr + 1;
		}
		ptr = ptr->next;
		num_lnks--;
	}
	return (1);
}

/*static	int 	what_status(t_list *lnks, char *room)
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
}*/

void			fill_searched(t_search **searched, t_search **search)
{
	t_search	*s1;
	t_search	*s2;
//TODO: IF ALL THE ROOMS IN LINKS OF THE ROOM THAT WE WANT TO ADD HAVE STATUS 1 THEN WE DO NOT ADD IT TO THE LIST OF SEARCHED
	s1 = *searched;
	s2 = *search;
	if ((*search)->step_nbr == 0)
	{
		s1->rooms = s2->rooms;
		s1->way_nbr = s2->way_nbr;
		s1->step_nbr = s2->step_nbr;
	}
	else
	{
		while (s1->next != NULL)
			s1 = s1->next;
		s1->next = (t_search *)ft_memalloc(sizeof(t_search));
		s1->next->prev = s1;
		s1->next->rooms = s2->rooms;
		s1->next->way_nbr = s2->way_nbr;
		s1->next->step_nbr = s2->step_nbr;
	}
	if ((*search)->next != NULL)
	{
		*search = (*search)->next;
		free(s2);
		s2 = NULL;
		(*search)->prev = NULL;
	}
	else
	{
		free(*search);
		*search = NULL;
	}
}

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

static	void	del_t_list_room(t_search **room)
{
	t_search *tmp;

	tmp = *room;
	tmp->next->prev = tmp->prev;
	tmp->prev->next = tmp->next;
	free(tmp);
	tmp = NULL;
}

static	void	make_it_clean(t_search **lst_rooms)
{
	t_search	*tmp;
	t_search	*tmp2;
	int			cnt;

	tmp = *lst_rooms;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp = tmp->prev;
	while (tmp->prev != NULL)
	{
		cnt = 0;
		if ((tmp->step_nbr >= tmp->next->step_nbr) || !it_has_link(tmp->rooms,
				tmp->next->rooms) || !it_has_link(tmp->rooms, tmp->prev->rooms))
		{
			if (!it_has_link(tmp->rooms, tmp->prev->rooms) && tmp->step_nbr < tmp->next->step_nbr && it_has_link(tmp->rooms, tmp->next->rooms))
			{
				tmp2 = tmp->prev;
				while (tmp2->prev != NULL)
				{
					if (it_has_link(tmp->rooms, tmp2->rooms) && tmp2->step_nbr < tmp->step_nbr)
					{
						cnt = 1;
						tmp2 = tmp2->next;
						while (!ft_strequ(tmp2->rooms->name, tmp->rooms->name))
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
					if (it_has_link(tmp->rooms, tmp2->rooms) && tmp2->step_nbr < tmp->step_nbr)
					{
						cnt = 1;
						tmp2 = tmp2->next;
						while (!ft_strequ(tmp2->rooms->name, tmp->rooms->name))
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

static	void	way_assignment(t_search *list)
{
	t_search *tmp;

	tmp = list;
	while (tmp)
	{
		tmp->rooms->way_nbr = (tmp->rooms->type == 0) ? tmp->way_nbr : -1;
		tmp->rooms->step_nbr = tmp->step_nbr;
		tmp = tmp->next;
	}
}

static	void	mark_the_way(t_search *list)
{
	t_search		*tmp;
	t_list			*ptr;
	t_list_links	*lnks;

	tmp = list;
	while (tmp)
	{
		ptr = tmp->rooms->links;
		while (1 && tmp->rooms->type != 2)
		{
			lnks = ptr->content;
			if ((ft_strequ(lnks->room1, tmp->rooms->name) && ft_strequ(lnks->
			room2, tmp->next->rooms->name)) || (ft_strequ(lnks->room2, tmp->
			rooms->name) && ft_strequ(lnks->room1, tmp->next->rooms->name)))
			{
				lnks->way_nbr = tmp->way_nbr;
				break;
			}
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
}

static	void	fill_the_way(t_way **tmp_way, t_search *list)
{
	make_it_clean(&list);
	way_assignment(list);
	mark_the_way(list);
	(*tmp_way)->rooms = ft_dllnew((void *)&(list->rooms), sizeof(t_list_rooms*));
	list = list->next;
	while (list->next != NULL)
	{
		ft_dlladdnextr(&((*tmp_way)->rooms), (void *)&(list->rooms), sizeof(t_list_rooms*));
		list = list->next;
	}
	ft_dlladdnextr(&((*tmp_way)->rooms), (void *)&(list->rooms), sizeof(t_list_rooms*));
	(*tmp_way)->len_way = list->step_nbr;
	(*tmp_way)->status = 1;
}

//TODO: 1. Return smth when we cannot find any new ways in current state

static int		end_searched(t_search *searched)
{
	t_search *tmp;

	tmp = searched;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->rooms->type == 2)
		return (1);
	return (0);
}

int		wide_search(t_find_way **fnd_way, t_intldta **indta)
{
	t_search	*search;
	t_search	*searched;
	t_way		*tmp_way;

	if ((*fnd_way)->ways == NULL)
	{
		(*fnd_way)->ways = (t_way *)ft_memalloc(sizeof(t_way));
		tmp_way = (*fnd_way)->ways;
		tmp_way->next = NULL;
		tmp_way->status = 1;
		tmp_way->prev = NULL;
		tmp_way->num_way = 1;
	}
	else
	{
		tmp_way = (*fnd_way)->ways;
		while (tmp_way->next != NULL)
			tmp_way = tmp_way->next;
		tmp_way->next = (t_way *)malloc(sizeof(t_way));
		tmp_way->next->prev = (*fnd_way)->ways;
		tmp_way->next->status = 1;
		tmp_way->next->num_way = tmp_way->num_way + 1;
		tmp_way->next->next = NULL;
		tmp_way = tmp_way->next;
	}
	search = (t_search *)ft_memalloc(sizeof(t_search));
	searched = (t_search *)ft_memalloc(sizeof(t_search));
	search->rooms = (*indta)->start_room;
	search->step_nbr = 0;
	search->way_nbr = tmp_way->num_way;
	while (1)
	{
		if (search != NULL && fill_search(fnd_way, &search, &searched))
			fill_searched(&searched, &search);
		else
			break ;
	}
	if (!end_searched(searched))//if in the end of searched end_room then fill the way, if not quit
	{
//		remove_way_nbr(&((*fnd_way)->ways)); //removing way_nbr from the rooms
		free_search_ed(&search, &searched);
		del_t_way(&tmp_way);
		return (0);
	}
	//the problem is here, i assign searched rooms, not the indta rooms, which is incorrect
	fill_the_way(&tmp_way, searched);
	print_the_way(&tmp_way);
	free_search_ed(&search, &searched);
	return (1);
}

void	cpy_t_list_room(t_list_rooms *dest, t_list_rooms *src, int way_nbr)
{
	dest = src;
	dest->way_nbr = way_nbr;
	dest->next = NULL;
}

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*find;

 	init_set(&find, indta);
	while (!rec_finding(indta, find))
		continue ;
	if (PRE && (CUR->full_steps == 0 || CUR->steps > PRE->steps))
		find->answer = PRE;
	else
		find->answer = CUR;
	print_the_answer(find->answer);
//	=> print answer
//	if (indta->v_flag)
//		visualizer(indta, find);
 	return (0);
}
