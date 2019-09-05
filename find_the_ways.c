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

int 	find_the_way(t_intldta *indta)
{
 	t_find_way			*find;

 	init_set(&find, indta);
//	if (indta->v_flag)
//		visualizer(indta, find);
	rev_wide_search(&indta);
	while (!rec_finding(indta, find))
		continue ;
	if (PRE && (CUR->full_steps == -1 || CUR->steps > PRE->steps))
		find->answer = PRE;
	else
		find->answer = CUR;
	print_the_answer(find->answer);
//	=> print answer
 	return (0);
}
