/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlldeltoleft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:11:55 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 16:06:00 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldeltoleft(t_dllist **alst, void (*del)(void*, size_t))
{
	if (!alst || !*alst || !del)
		return ;
	ft_dlldeltoleft(&alst[0]->left, del);
	ft_dlldelone(alst, del);
	alst = NULL;
}
