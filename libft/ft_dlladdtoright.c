/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlladdtoright.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:17:35 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 13:26:30 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddtoright(t_dllist **alst, t_dllist *new)
{
	if (!alst || !new || *alst)
		return ;
	new->left = *alst;
	alst[0]->right = new;
	*alst = new;
}
