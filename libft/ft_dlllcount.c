/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlllcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:38:13 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 13:41:40 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dlllcount(t_dllist *addr)
{
	int		count;

	if (addr == NULL)
		return (0);
	count = 0;
	while (addr != NULL)
	{
		count++;
		addr = addr->left;
	}
	return (count);
}
