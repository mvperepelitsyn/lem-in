/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlldeltoright.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:58:58 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 16:08:05 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldeltoright(t_dllist **alst, void (*del)(void*, size_t))
{
	if (!alst || !*alst || !del)
		return ;
	ft_dlldeltoright(&alst[0]->right, del);
	ft_dlldelone(alst, del);
	alst = NULL;
}
