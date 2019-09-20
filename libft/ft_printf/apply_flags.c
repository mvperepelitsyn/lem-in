/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:33:20 by uhand             #+#    #+#             */
/*   Updated: 2019/05/22 13:56:30 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		join_buf(t_printf *p, t_format *f)
{
	int		len;
	int		i;
	char	*buf;

	len = p->len + f->len;
	if (!(buf = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	buf[len] = '\0';
	i = -1;
	while (++i < p->len)
		buf[i] = p->str[i];
	i = -1;
	while ((p->len + ++i) < len)
		buf[p->len + i] = f->str[i];
	free(p->str);
	free(f->str);
	p->str = buf;
	p->len = len;
	return (1);
}

void	char_shift(t_format *f)
{
	int		i;

	i = f->len - 1;
	while (i > 0)
	{
		f->str[i] = f->str[i - 1];
		i--;
	}
	f->str[i] = ' ';
}

int		float_flags(t_printf *p, t_format *f)
{
	if (!join_buf(p, f))
		return (0);
	return (1);
}

int		char_flags(t_printf *p, t_format *f)
{
	int		diff;
	char	c;

	if (f->width > f->len)
	{
		diff = f->width - f->len;
		c = ' ';
		if (f->flags[3])
		{
			if (!addnspaces(f, c, diff))
				return (0);
		}
		else
		{
			if ((f->flags[2] && f->precision < 0 && !(f->type == 3)) || \
				(f->flags[2] && (f->type == 0 || f->type == 1 || f->type == 9)))
				c = '0';
			if (!addnchar(p, c, diff))
				return (0);
		}
	}
	if (f->type == 0 || f->type == 1 || f->type == 3 || f->type == 9)
		if (!join_buf(p, f))
			return (0);
	return (1);
}

int		int_flags(t_printf *p, t_format *f)
{
	if (!char_flags(p, f))
		return (0);
	if (f->flags[0] && f->type == 4 && !f->flags[4] && f->str[0] != '-' \
		&& f->str[0] != ' ' && f->start == -1)
	{
		if (f->str[0] == '0' && f->len > 1)
			f->str[0] = ' ';
		else if (f->str[f->len - 1] == ' ')
			char_shift(f);
		else
			addnchar(p, ' ', 1);
	}
	else if (f->flags[0] && f->start != -1 && f->type == 4 && !f->flags[4] \
		&& p->str[f->start] != '-')
		p->str[f->start] = ' ';
	if (!join_buf(p, f))
		return (0);
	return (1);
}
