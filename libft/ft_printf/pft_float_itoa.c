/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_float_itoa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 11:00:08 by uhand             #+#    #+#             */
/*   Updated: 2019/05/22 20:25:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*join_float_string(t_format *f, t_fl_string *s, t_fl_itoa *a)
{
	int		i;

	i = 0;
	if (!(f->str = ft_strnew(f->len + 1)))
		return (free_float_parts(s->w_part, s->f_part));
	f->str[f->len] = '\0';
	if (s->dif <= 1)
	{
		if (s->dif == 1)
		{
			if (f->flags[3] && !(f->flags[4] || a->sign == 1 || f->flags[0]))
				f->str[f->len - 1] = ' ';
			else
				add_sign_or_zero(a, f, s, &i);
		}
		pft_strncpy(&f->str[i], s->w_part, s->w_len);
		pft_strncpy(&f->str[s->w_len + i], s->f_part, s->f_len);
	}
	else
		f->str = add_first_part_of_string(a, f, s, 0);
	free_float_parts(s->w_part, s->f_part);
	return (f->str);
}

static void	set_float_string(char *str, unsigned long long num, int order, \
	int param)
{
	if (param)
		str[order] = '.';
	while (order > 0)
	{
		str[order - 1] = (num % 10) + 48;
		num /= 10;
		order--;
	}
}

void		set_float_string_fract(char *str, unsigned long long num, \
	int order, t_fl_itoa *a)
{
	int		i;

	i = 0;
	while ((a->frc_order + i) < a->prec)
	{
		str[i] = '0';
		i++;
	}
	while (order > 0)
	{
		str[i + order - 1] = (num % 10) + 48;
		num /= 10;
		order--;
	}
}

char		*pft_zero_itoa(t_format *f, t_fl_itoa *a, t_fl_string *s)
{
	int		i;

	if (a->frc && !(f->precision > a->prec))
	{
		if (!(s->f_part = ft_strnew(a->prec + 1)))
			return (NULL);
		s->f_part[a->frc_order] = '\0';
		set_float_string_fract(s->f_part, a->frc, a->frc_order, a);
		f->len += a->prec;
		s->f_len = a->prec;
	}
	else if (a->frc && f->precision > a->prec)
		return (add_some_bagels(f, a, s));
	else
	{
		if (!(s->f_part = ft_strnew(f->precision + 1)))
			return (NULL);
		s->f_part[f->precision] = '\0';
		i = -1;
		while (++i < f->precision)
			s->f_part[i] = '0';
		f->len += f->precision;
		s->f_len = f->precision;
	}
	return (s->f_part);
}

char		*pft_whole_itoa(t_format *f, unsigned long long whole, \
	t_fl_string *s)
{
	int		dot;
	int		order;

	dot = 0;
	order = get_order(whole);
	s->w_len = order;
	if (f->precision > 0 || f->flags[1])
	{
		s->w_len++;
		dot = 1;
	}
	if (!(s->w_part = ft_strnew(s->w_len + 1)))
		return (NULL);
	s->w_part[s->w_len] = '\0';
	set_float_string(s->w_part, whole, order, dot);
	return (s->w_part);
}
