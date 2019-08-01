/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:42:21 by uhand             #+#    #+#             */
/*   Updated: 2019/07/17 20:06:42 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

# define P format[p->i]

typedef struct s_printf	t_printf;
typedef struct s_format	t_format;
typedef	int				(*t_method)(t_printf *p, t_format *f, void *data);

/*
** Current format's params: f
*/

struct				s_format
{
	int					width;
	int					precision;
	int					type;
	int					len;
	int					start;
	char				flags[5];
	char				length[2];
	char				*str;
};

/*
** Operational format string's params: p
*/

struct				s_printf
{
	int					start;
	int					i;
	int					len;
	int					*f_start;
	char				*str;
	t_method			method_arr[10];
};

/*
** Float itoa's params: a
*/

typedef struct		s_fl_itoa
{
	double				arg;
	long double			num;
	unsigned long long	whl;
	unsigned long long	frc;
	int					frc_order;
	int					prec;
	unsigned char		sign;
	short				exp;
	unsigned long long	mant;
}					t_fl_itoa;

/*
** Float string's params: s
*/

typedef struct		s_fl_string
{
	char				*w_part;
	char				*f_part;
	int					w_len;
	int					f_len;
	int					dif;
}					t_fl_string;

/*
** Long precision params: l
*/

typedef struct		s_lprec
{
	long double			frc;
	char				*f_part;
	int					i;
}					t_lprec;

int					ft_printf(const char *format, ...);
int					ft_sprintf(char *str, const char *format, ...);
int					ft_fdprintf(int fd, const char *format, ...);
void				tprintf_init(t_printf *p);
int					join_f(const char *format, t_printf *p);
int					free_buf(t_printf *p);
int					free_str(t_format *f);
int					addnchar(t_printf *p, char c, int n);
void				pft_strncpy(char *dst, const char *src, size_t len);
void				tformat_init(t_format *f, t_printf *p);
int					addnspaces(t_format *f, char c, int n);
char				*pft_itoa(long long n, t_format *f);
char				*pft_unsigned_itoa(unsigned long long num, t_format *f);
int					pft_order(unsigned long long num, t_format *f);
void				set_string(char *str, unsigned long long num, int order, \
	int dif);
void				char_shift(t_format *f);
int					join_buf(t_printf *p, t_format *f);
char				*pft_zero_itoa(t_format *f, t_fl_itoa *a, t_fl_string *s);
char				*pft_whole_itoa(t_format *f, unsigned long long whole, \
	t_fl_string *s);
int					get_order(unsigned long long num);
char				*join_float_string(t_format *f, t_fl_string *s, \
	t_fl_itoa *a);
char				*free_float_parts(char *str1, char *str2);
void				add_sign_or_zero(t_fl_itoa *a, t_format *f, \
	t_fl_string *s, int *i);
void				left_side_starters(t_fl_itoa *a, t_format *f, \
	t_fl_string *s, int *i);
char				*add_some_bagels(t_format *f, t_fl_itoa *a, t_fl_string *s);
char				*add_first_part_of_string(t_fl_itoa *a, t_format *f, \
	t_fl_string *s, int i);
unsigned long long	put_ordr(int order);
void				set_float_string_fract(char *str, unsigned long long num, \
	int order, t_fl_itoa *a);
char				*get_long_precision (t_format *f, t_fl_itoa *a);
void				get_double_rep(t_fl_itoa *a);
int					check_int_and_nan(t_fl_itoa *a, t_format *f);

void				set_flags(t_printf *p, const char *format, t_format *f);
void				set_wnp(t_printf *p, const char *format, t_format *f, \
	va_list *ap);
void				set_length(t_printf *p, const char *format, t_format *f);
void				set_type(char c, t_format *f);
int					char_flags(t_printf *p, t_format *f);
int					int_flags(t_printf *p, t_format *f);
int					float_flags(t_printf *p, t_format *f);

int					format_c(t_printf *p, t_format *f, va_list *ap);
int					format_s(t_printf *p, t_format *f, va_list *ap);
int					format_p(t_printf *p, t_format *f, va_list *ap);
int					format_f(t_printf *p, t_format *f, va_list *ap);
int					format_d(t_printf *p, t_format *f, va_list *ap);
int					format_oux(t_printf *p, t_format *f, va_list *ap);
#endif
