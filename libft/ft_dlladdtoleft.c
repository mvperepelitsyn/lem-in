/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlladdtoleft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:14:38 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 13:26:31 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddtoleft(t_dllist **alst, t_dllist *new)
{
	if (!alst || !new || *alst)
		return ;
	new->right = *alst;
	alst[0]->left = new;
	*alst = new;
}
