/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_itoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:45:16 by uhand             #+#    #+#             */
/*   Updated: 2019/04/25 16:54:50 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			pft_order(unsigned long long num, t_format *f)
{
	int		order;

	if (num == 0)
	{
		if (f->precision == 0)
			return (0);
		return (1);
	}
	order = 0;
	while (num > 0)
	{
		num /= 10;
		order++;
	}
	return (order);
}

void		set_string(char *str, unsigned long long num, int order, int dif)
{
	while (order > 0)
	{
		str[order + dif - 1] = (num % 10) + 48;
		num /= 10;
		order--;
	}
	while (++order < dif)
		str[order] = '0';
}

static void	check_sign_n_prec(int *dif, long long n, t_format *f)
{
	*dif = 0;
	if (f->len < f->precision)
	{
		*dif = f->precision - f->len;
		f->len = f->precision;
	}
	if (f->flags[4] || n < 0)
	{
		f->len++;
		if (f->width > f->len && f->flags[2] && !f->flags[3])
			f->len = f->width;
	}
}

char		*pft_itoa(long long n, t_format *f)
{
	char				*str;
	unsigned long long	num;
	int					dif;

	if (n < 0)
		num = (unsigned long long)(-n);
	else
		num = (unsigned long long)n;
	f->len = pft_order(num, f);
	check_sign_n_prec(&dif, n, f);
	if (!(str = ft_strnew(f->len)))
		return (NULL);
	if (f->flags[4] || n < 0)
	{
		if (n < 0)
			str[0] = '-';
		else
			str[0] = '+';
		dif++;
	}
	else
		str[0] = '0';
	set_string(str, num, (f->len - dif), dif);
	return (str);
}
