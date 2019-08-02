/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 19:07:00 by uhand             #+#    #+#             */
/*   Updated: 2019/08/01 19:55:05 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void set_limits(t_intldta *indta)
{
    //
}

static void build_graph(t_intldta *indta)
{
    //
}

void        visualizer(t_intldta *indta)
{
    t_graph g;

    set_limits(indta, &g);
    build_graph(indta);
}