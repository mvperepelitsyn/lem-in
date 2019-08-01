/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlldel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:57:34 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 15:39:33 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldel(t_dllist **alst, void (*del)(void*, size_t))
{
	t_dllist	*left;
	t_dllist	*right;

	if (!alst || !*alst || !del)
		return ;
	right = alst[0]->right;
	left = alst[0]->left;
	ft_dlldeltoright(&right, del);
	ft_dlldeltoright(&right, del);
	ft_dlldelone(alst, del);
	alst = NULL;
}
