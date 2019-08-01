/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:56:40 by uhand             #+#    #+#             */
/*   Updated: 2019/01/21 19:13:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcount(t_list *addr)
{
	int		count;

	if (addr == NULL)
		return (0);
	count = 0;
	while (addr != NULL)
	{
		count++;
		addr = addr->next;
	}
	return (count);
}
