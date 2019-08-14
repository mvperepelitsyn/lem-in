/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:46:45 by uhand             #+#    #+#             */
/*   Updated: 2019/08/14 13:27:05 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		deal_key(int key, void *prm)
{
	t_vis_prms	*v;

	v = (t_vis_prms*)prm;
	if (key == 53)
		return (close_vis(prm));
	return (0);
}

int		close_vis(void *prm)
{
	t_vis_prms	*v;

	v = (t_vis_prms*)prm;
	mlx_destroy_image(v->mlx_ptr, v->img_ptr);
	mlx_destroy_window(v->mlx_ptr, v->win_ptr);
	exit(0);
	return (0);
}
