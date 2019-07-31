//
// Created by Dwarven centurion Frost atronach on 2019-07-31.
//

#include "finding.h"

void	init_graph(t_graph **graph, t_intldta *indta)
{
	(*graph) = (t_graph *)malloc(sizeof(t_graph));
	(*graph)->nod->nod_nme = ft_strsub(indta->start_room->name, 0, ft_strlen(indta->start_room->name));
	(*graph)->nod->num_lnks = -1;
	(*graph)->nod->lnod = NULL;
	(*graph)->next = NULL;
}

int 	make_the_graph(t_intldta *indta)
{
	t_graph *graph;

	init_graph(&graph, indta);
}