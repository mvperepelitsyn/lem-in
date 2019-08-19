/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:06:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/19 15:25:51 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_WAY_H
# define FIND_WAY_H

# include "./parser.h"

/*
** Way params: way
*/

//typedef struct		s_way
//{
//	int 			len_way;
//	int 			num_way;
//	t_list_rooms	*rooms;
//}					t_way;
//
//typedef struct 		s_ways
//{
//	t_way			*way;
//	struct s_ways	*next;
//}					t_ways;
//
///*
//** Way set params: set
//*/
//
//typedef struct			s_way_set
//{
//	int					steps_cnt;
//	int					ways_cnt;
//	t_ways				*ways;
//	struct s_way_set	*next;
//}						t_way_set;

typedef struct		s_way
{
	int				len_way;
	int				num_way;
	t_list			*rooms;
	struct s_way	*next;
}					t_way;

/*
** Way set params: set
*/

typedef struct			s_way_set
{
	int					steps;
	int					ways_cnt;
	t_list				*ways;
	struct s_way_set	*next;
}						t_way_set;

/*
** find_the_way params: find
*/

typedef struct	s_find_way
{
	t_way_set		*crnt_set;  // сurrent set
	t_way_set		*prev_set;	// previous set
	t_way			*ways;
	int 			way_nbr;
	t_list_rooms	*start;
}				t_find_way;

int 	find_the_way(t_intldta *indta);
void	cpy_t_list_room(t_list_rooms *dest, t_list_rooms *src);

#endif
