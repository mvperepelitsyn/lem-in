/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 18:06:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/16 18:20:50 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_WAY_H
# define FIND_WAY_H

# include "./parser.h"

/*
** Way params: way
*/

typedef struct	s_way
{
	//
}				t_way;

/*
** Way set params: set
*/

typedef struct	s_way_set
{
	int					steps_cnt;
	int					ways_cnt;
	t_list				*ways;
	struct s_way_set	*next;
}				t_way_set;

/*
** find_the_way params: find
*/

typedef struct	s_find_way
{
	//
}				t_find_way;

#endif
