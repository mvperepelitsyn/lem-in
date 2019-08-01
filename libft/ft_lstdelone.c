/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:47:04 by uhand             #+#    #+#             */
/*   Updated: 2019/07/24 20:24:33 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if (!alst || !alst[0] || !del)
		return ;
	if (alst[0] && alst[0]->content)
		del(alst[0]->content, alst[0]->content_size);
	free(alst[0]);
	alst[0] = NULL;
}
