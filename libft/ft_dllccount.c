/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllccount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:42:59 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 16:46:17 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_dllccount(t_dllist *addr)
{
	t_dllist	*left;
	int			count;

	if (addr == NULL)
		return (0);
	left = addr->left;
	count = 0;
	while (addr != NULL)
	{
		count++;
		addr = addr->right;
	}
	while (left != NULL)
	{
		count++;
		addr = addr->left;
	}
	return (count);
}
