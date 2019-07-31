//
// Created by Dwarven centurion Frost atronach on 2019-07-31.
//

#ifndef LEM_IN_FINDING_H
# define LEM_IN_FINDING_H

# include "parser.h"

typedef struct			s_way
{
	char 				*room;
	struct s_way 		*next;
	struct s_way		*prev;
}						t_way;

typedef	struct			s_nod_links
{
	char 				*lnod_nme;
	struct s_nod_links	*next;
}						t_nod_links;

typedef	struct 			s_nod
{
	char 				*nod_nme;
	int 				num_lnks;
	t_nod_links			*lnod;
}						t_nod;

typedef struct 			s_graph
{
	t_nod				*nod;
	struct s_graph		*next;
}						t_graph;

int 	find_the_way(t_intldta *indta);


int 	make_the_graph(t_intldta *indta);

#endif //LEM_IN_FINDING_H
