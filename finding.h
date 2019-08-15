//
// Created by Dwarven centurion Frost atronach on 2019-07-31.
//

#ifndef LEM_IN_FINDING_H
# define LEM_IN_FINDING_H

# include "parser.h"

typedef struct		s_way
{
	char 			*room;
	struct s_way 	*next;
	struct s_way	*prev;
}					t_way;

typedef struct 		s_flow
{
	t_way			*way;
	int 			length_way;
	struct s_flow	*next;
}					t_flow;

int 	find_the_way(t_intldta *indta);

#endif //LEM_IN_FINDING_H
