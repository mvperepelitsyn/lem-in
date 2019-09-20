/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_rep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:38:58 by uhand             #+#    #+#             */
/*   Updated: 2019/09/18 17:18:35 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	set_inf_or_nan(int len, char *str, t_format *f)
{
	f->len = len;
	if (!(f->str = (char*)malloc(sizeof(char) * (f->len + 1))))
		return (-1);
	f->str[f->len] = '\0';
	pft_strncpy(f->str, str, f->len);
	return (1);
}

int			check_int_and_nan(t_fl_itoa *a, t_format *f)
{
	f->len = 3;
	if (a->arg != a->arg)
		return (set_inf_or_nan(3, "nan", f));
	if (a->exp == 1024 && a->mant == 0)
	{
		if (a->sign)
			return (set_inf_or_nan(4, "-inf", f));
		else if (!f->flags[4])
		{
			if (!f->flags[0])
				return (set_inf_or_nan(3, "inf", f));
			else
				return (set_inf_or_nan(4, " inf", f));
		}
		else
			return (set_inf_or_nan(4, "+inf", f));
	}
	return (0);
}

void		get_double_rep(t_fl_itoa *a)
{
	double				n_cpy;
	unsigned char		*sign;
	unsigned short		*exp;
	unsigned long long	*mant;

	n_cpy = a->arg;
	sign = (unsigned char*)&n_cpy;
	sign += 7;
	a->sign = *sign;
	a->sign >>= 7;
	n_cpy = a->arg;
	exp = (unsigned short*)&n_cpy;
	exp += 3;
	*exp = *exp << 1;
	*exp = *exp >> 5;
	a->exp = *exp;
	a->exp -= 1023;
	n_cpy = a->arg;
	mant = (unsigned long long*)&n_cpy;
	a->mant = *mant;
	a->mant <<= 12;
	a->mant >>= 12;
}
