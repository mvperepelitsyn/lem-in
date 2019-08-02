/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:11:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/02 15:53:11 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_VISUALIZER_H
#define LEM_IN_VISUALIZER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../minilibx/mlx.h"
# include "../parser.h"

# define WIN_X 2560
# define WIN_Y 1575
# define R 10
# define SCALE 10

void    visualizer(t_intldta *indta);
//void    set_limits(t_intldta *indta);
//void    build_graph(t_intldta *indta);

/*
** Graph vis params: g
*/

typedef struct	s_graph
{
	int 	min_x;
	int 	min_y;
	int 	max_x;
	int 	max_y;
	int 	scale;
	int 	delta_x;
	int 	delta_y;
}				t_graph;


#endif
