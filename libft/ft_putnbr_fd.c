/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:21:48 by uhand             #+#    #+#             */
/*   Updated: 2018/12/04 19:21:52 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 10)
	{
		ft_putchar_fd(49, fd);
		n = 0;
	}
	if (n == -2147483648)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putchar_fd('8', fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 10)
		ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd(((n % 10) + 48), fd);
}
