/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_float_itoa_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 16:29:13 by uhand             #+#    #+#             */
/*   Updated: 2019/07/18 17:08:09 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*add_first_part_of_string(t_fl_itoa *a, t_format *f, \
	t_fl_string *s, int i)
{
	if (!f->flags[3])
		left_side_starters(a, f, s, &i);
	else if (a->sign == 1 || f->flags[4] || f->flags[0])
		add_sign_or_zero(a, f, s, &i);
	pft_strncpy(&f->str[i], s->w_part, s->w_len);
	pft_strncpy(&f->str[s->w_len + i], s->f_part, s->f_len);
	while (s->dif > 0)
	{
		f->str[f->len - s->dif] = ' ';
		s->dif--;
	}
	return (f->str);
}

static char	*get_long_float_string(t_format *f, t_fl_itoa *a, char *f_part)
{
	t_fl_string			s;

	s.w_part = NULL;
	s.f_part = f_part;
	s.f_len = f->len;
	a->frc_order = s.f_len;
	s.dif = 0;
	if (!(s.w_part = pft_whole_itoa(f, a->whl, &s)))
		return (NULL);
	f->len += s.w_len;
	if (f->width > f->len)
	{
		s.dif = f->width - f->len;
		f->len = f->width;
	}
	else if (f->flags[4] || f->flags[0] || a->sign == 1)
	{
		f->len++;
		s.dif++;
	}
	return (join_float_string(f, &s, a));
}

static void	round_float_str(t_fl_itoa *a, t_lprec *l)
{
	int		i;

	i = a->prec - 1;
	l->f_part[i]++;
	while (i >= 0)
	{
		if (i == 0)
		{
			if (l->f_part[i] == 10)
			{
				l->f_part[i] = 0;
				a->whl++;
			}
		}
		else if (l->f_part[i] == 10)
		{
			l->f_part[i] = 0;
			l->f_part[i - 1]++;
		}
		i--;
	}
}

char		*get_long_precision(t_format *f, t_fl_itoa *a)
{
	t_lprec	l;

	l.frc = (long double)(a->num - a->whl);
	if (!(l.f_part = ft_strnew(a->prec + 2)))
		return (NULL);
	l.i = 0;
	while (l.i <= a->prec)
	{
		l.frc = l.frc - (unsigned long long)l.frc;
		l.frc = l.frc * 10;
		a->frc = (unsigned long long)l.frc;
		l.f_part[l.i] = a->frc;
		l.i++;
	}
	if (l.f_part[a->prec] < 5)
		l.f_part[a->prec] = '\0';
	else
		round_float_str(a, &l);
	while (--l.i >= 0)
		l.f_part[l.i] += 48;
	f->len = f->precision;
	return (get_long_float_string(f, a, l.f_part));
}
