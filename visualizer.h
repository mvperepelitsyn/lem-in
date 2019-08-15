/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:11:04 by uhand             #+#    #+#             */
/*   Updated: 2019/08/15 15:40:16 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_VISUALIZER_H
#define LEM_IN_VISUALIZER_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "./parser.h"

# define WIN_X 2560
# define WIN_Y 1575
# define R 10
# define SCALE 2000
# define S_CLR 0x00FF00
# define F_CLR 0xFF0000
# define R_CLR 0xFFFFFF

typedef struct s_vis_prms	t_vis_prms;


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
	int			clr[3];
	t_vis_prms	*v;
}				t_graph;

/*
**	visualizer params: v
*/

struct			s_vis_prms
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
};

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
	t_vis_prms		*img;
}				t_line_prm;

/*
** Operational build circle params: c
*/

typedef struct	s_circle
{
	int				x;
	int				y;
	int				r;
	int				clr;
}				t_circle;

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

/*
** Current dot params: a, b
*/

typedef struct	s_pix_prm
{
	int				x;
	int				y;
	int				color;
}				t_pix_prm;

void	visualizer(t_intldta *indta);
void	draw_rooms(t_intldta *indta, t_graph *g);
void	draw_links(t_intldta *indta, t_graph *g);
int		put_pix_to_img(t_line_prm *l, int x, int y, int color);
void	put_line_to_img(t_vis_prms *v, t_pix_prm a, t_pix_prm b);
void	set_grad_color(t_grad *g, t_grad_prms *clr, int pos);
int		deal_key(int key, void *prm);
int		close_vis(void *prm);
void	trim_line(t_pix_prm *a, t_pix_prm *b, int r);

#endif
