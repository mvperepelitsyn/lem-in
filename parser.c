/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 17:18:02 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/02 17:18:24 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
//
//void	ft_freestr(int wrd, char **str)
//{
//	int i;
//
//	i = 0;
//	while (i < wrd)
//	{
//		free(str[i]);
//		str[i] = NULL;
//		i++;
//	}
//	free(str);
//}

//void	help_parse_args(int argc, char **argv, t_stack *stack)
//{
//	int		swtch;
//	char	**str;
//
//	swtch = 0;
//	if (argc == 2)
//	{
//		swtch = 1;
//		argc = ft_hm_wrd(argv[1], ' ') + 1;
//		str = ft_strsplit(argv[1], ' ');
//		init_stack(stack, argc);
//		parse_args2(stack, str, swtch, argc);
//		ft_freestr(argc, str);
//	}
//	else
//	{
//		init_stack(stack, argc);
//		parse_args1(stack, argv, argc);
//	}
//}
//
//short	duplic(const int *tmp, int size, int dupl)
//{
//	int i;
//
//	i = 0;
//	while (++i <= size)
//	{
//		if (tmp[i] == dupl)
//			return (1);
//	}
//	return (0);
//}
//
//void	parse_args1(t_stack *stack, char **argv, int nbr)
//{
//	int *tmp;
//	int i;
//	int j;
//
//	i = 0;
//	j = 0;
//	tmp = (int *)malloc(sizeof(int) * (stack->a_size + 1));
//	while (nbr > 1)
//	{
//		++i;
//		if (!(ft_isintnumber(argv[i])))
//			ft_error();
//		tmp[i] = ft_atoi(argv[i]);
//		if (duplic(tmp, i - 1, tmp[i]))
//			ft_error();
//		nbr--;
//	}
//	while ((i) > 0)
//	{
//		stack->a_stack[++j] = tmp[i];
//		i--;
//	}
//	free(tmp);
//}
//
//void	parse_args2(t_stack *stack, char **argv, short swtch, int nbr)
//{
//	int *tmp;
//	int i;
//	int j;
//
//	i = (swtch == 1) ? -1 : 0;
//	j = 0;
//	tmp = (int *)malloc(sizeof(int) * (stack->a_size + 1));
//	while (nbr > 1)
//	{
//		++i;
//		if (!(ft_isintnumber(argv[i])))
//			ft_error();
//		tmp[i + swtch] = ft_atoi(argv[i]);
//		if (duplic(tmp, i, tmp[i + swtch]))
//			ft_error();
//		nbr--;
//	}
//	while ((i + swtch) > 0)
//	{
//		stack->a_stack[++j] = tmp[i + swtch];
//		i--;
//	}
//	free(tmp);
//}
