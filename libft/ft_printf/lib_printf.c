/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 13:55:11 by uhand             #+#    #+#             */
/*   Updated: 2019/04/28 15:05:27 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = (char)src[i];
		i++;
	}
}

int		addnspaces(t_format *f, char c, int n)
{
	char	*buf;
	int		len;
	int		i;

	if (n <= 0)
		return (1);
	len = f->len + n;
	if (!(buf = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	buf[len] = '\0';
	pft_strncpy(buf, f->str, f->len);
	i = 0;
	while (i < n)
	{
		buf[f->len + i] = c;
		i++;
	}
	free(f->str);
	f->str = buf;
	f->len = len;
	return (1);
}

int		addnchar(t_printf *p, char c, int n)
{
	char	*buf;
	int		len;
	int		i;

	if (n <= 0)
		return (1);
	len = p->len + n;
	if (!(buf = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	buf[len] = '\0';
	pft_strncpy(buf, p->str, p->len);
	i = 0;
	if (c != '%')
		*p->f_start = p->len + i;
	while (i < n)
	{
		buf[p->len + i] = c;
		i++;
	}
	free(p->str);
	p->str = buf;
	p->len = len;
	return (1);
}

int		join_f(const char *format, t_printf *p)
{
	int		len;
	char	*buf;

	len = p->i - p->start;
	if (p->str == NULL)
	{
		if (!(p->str = (char*)malloc(sizeof(char) * (len + 1))))
			return (0);
		pft_strncpy(p->str, &format[p->start], (len));
		p->str[len] = '\0';
		p->len = len;
		return (1);
	}
	if (!(buf = (char*)malloc(sizeof(char) * (p->len + len + 1))))
		return (0);
	pft_strncpy(buf, p->str, p->len);
	pft_strncpy(&buf[p->len], &format[p->start], len);
	p->len += len;
	buf[p->len] = '\0';
	free(p->str);
	p->str = buf;
	return (1);
}
