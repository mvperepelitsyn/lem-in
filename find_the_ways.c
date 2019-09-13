#include "lem_in.h"

void			print_the_way(t_way *way)
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
	ft_printf("\t:%d", (*way).len_way);
	if ((*way).len_way == 60)
		(*way).len_way = 60;
	ft_putstr("\n");
}

void		print_the_answer(t_way_set	*answer)
{
	ft_printf("BEWARE! THE ANSWER SET OF WAYS:");
	print_the_set(answer);
}

static void	init_set(t_find_way **fnd_wy, t_intldta *indta)
{
 	if (!((*fnd_wy) = (t_find_way *)ft_memalloc(sizeof(t_find_way))))
 		ft_malloc_error();
	(*fnd_wy)->ways = NULL;
	(*fnd_wy)->start = indta->start_room;
	(*fnd_wy)->sets = NULL;
	(*fnd_wy)->crnt_set = NULL;
	(*fnd_wy)->way_nbr = 0;
	(*fnd_wy)->del_room = NULL;
	(*fnd_wy)->check = 1;
}

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*find;
	int					steps;
	t_way_set			*ptr;

 	init_set(&find, indta);
	rev_wide_search(&indta);
	(*indta).start_room->tmp_step_nbr = 0;
	if (indta->start_room->act_lnks == 0)
	{
		free(find);
		return (1);
	}
	while (!rec_finding(indta, find))
		continue ;
	find->answer = find->sets;
	ptr = find->answer;
	steps = ptr->steps;
	while (ptr)
	{
		if (ptr->steps < steps)
		{
			find->answer = ptr;
			steps = ptr->steps;
		}
		ptr = ptr->next;
	}
	print_the_answer(find->answer);
//	if (indta->v_flag)
//		visualizer(indta, find);
	move_ants(indta, find);
 	return (0);
}
