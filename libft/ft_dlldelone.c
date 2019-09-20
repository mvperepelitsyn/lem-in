/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlldelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:55:51 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 12:57:38 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlldelone(t_dllist **alst, void (*del)(void*, size_t))
{
	if (!alst || !*alst || !del)
		return ;
	del(alst[0]->content, alst[0]->content_size);
	free(alst[0]);
	alst[0] = NULL;
}
