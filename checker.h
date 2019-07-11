/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfrost-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 13:35:18 by dfrost-a          #+#    #+#             */
/*   Updated: 2019/07/11 16:41:23 by dfrost-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_CHECKER_H
# define PUSH_SWAP_CHECKER_H

# include "libft/includes/libft.h"

typedef struct	s_room
{
	char *name;
	int x_cord;
	int y_cord;
}				t_room;

typedef struct		s_list_rooms
{
	t_room				*room;
	int 				i;
	struct s_list_rooms	*next;
}					t_list_rooms;

typedef struct		s_list_links
{
	char				*room1;
	char 				*room2;
	int 				i;
	struct s_list_links *next;
}					t_list_links;

typedef struct	s_test
{
	int				num_ants;
	t_list_rooms	*rooms;
	t_list_links	*links;
	t_room			*start_room;
	t_room			*end_room;
}				t_test;

void	ft_malloc_error(void);

#endif
