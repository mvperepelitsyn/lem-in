/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:11:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/02 19:14:24 by uhand            ###   ########.fr       */
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
# define S_CLR 0x00FF00
# define F_CLR 0xFF0000
# define R_CLR 0xFFFFFF

/*
** Graph vis params: g
*/

typedef struct	s_graph
{
	int 		min_x;
	int 		min_y;
	int 		max_x;
	int 		max_y;
	int 		scale;
	int 		delta_x;
	int 		delta_y;
	t_vis_prms	*v;
}				t_graph;

/*
**	visualizer params: v
*/

typedef struct	s_vis_prms
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		bpp;
	int		lsz;
	int		ndn;
	int 	win_x;
	int 	win_y;
}				t_vis_prms;

/*
** Operational build line params: l
*/

typedef struct	s_line_prm
{
	int				dx;
	int				dy;
	int				d_big;
	int				d_small;
	int				i;
	int				d_ind;
	int				sign;
	t_img_data		*img;
}				t_line_prm;

/*
** Input grad params: clr
*/

typedef struct	s_grad_prms
{
	int				delta;
	int				a;
	int				b;
}				t_grad_prms;

/*
** Operational grad params: grad
*/

typedef struct	s_grad
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	*c;
	int				d_alpha;
	int				d1;
	int				d2;
	int				d3;
	int				color;
	int				start;
	int				alpha;
}				t_grad;

void	visualizer(t_intldta *indta);
void	draw_rooms(t_intldta *indta, t_graph *g);
void	draw_links(t_intldta *indta, t_graph *g);

#endif
