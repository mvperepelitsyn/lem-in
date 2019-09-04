#include "lem_in.h"

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

void		print_the_way(t_way *way)
{
	t_way			*tmp;
	t_dllist		*ptr;
	t_list_rooms	**ptr2;
	t_list_rooms	*ptr3;

	tmp = way;
	ptr = tmp->rooms;
	ft_putstr("\n");
	while (ptr != NULL)
	{
		ptr2 = ptr->content;
		ptr3 = (*ptr2);
		if (ptr->right != NULL)
			ft_printf("%s->", ptr3->name);
		else
			ft_printf("%s", ptr3->name);
		ptr = ptr->right;
	}
	ft_putstr("\n");
}

//void		print_the_answer(t_way_set	*answer)
//{
//	t_list	*list_ways;
//	t_way	**tmp;
//
//	list_ways = answer->ways;
//	ft_printf("Here is a set of ways, that would be the best for our ant-farm:");
//	while (list_ways)
//	{
//		tmp = list_ways->content;
//		print_the_way(*tmp);
//		list_ways = list_ways->next;
//	}
//}

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
		if (((ft_strequ(rm_1->name, lnks->room1) && ft_strequ(room2->name,
				lnks->room2)) || (ft_strequ(room2->name, lnks->room1) &&
				ft_strequ(rm_1->name, lnks->room2))) && lnks->status == 1)
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

void	fill_the_way(t_way **tmp_way, t_search *list)
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
	print_the_way(*tmp_way);
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
//	if (indta->v_flag)
//		visualizer(indta, find);
	while (!rec_finding(indta, find))
		continue ;
	if (PRE && (CUR->full_steps == 0 || CUR->steps > PRE->steps))
		find->answer = PRE;
	else
		find->answer = CUR;
	print_the_set(find->answer);
//	=> print answer
 	return (0);
}
