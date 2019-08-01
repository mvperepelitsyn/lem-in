/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:47:05 by uhand             #+#    #+#             */
/*   Updated: 2019/06/24 12:51:44 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dllist	*ft_dllnew(void const *content, size_t content_size)
{
	t_dllist	*new_list;

	if (!(new_list = (t_dllist*)malloc(sizeof(t_dllist))))
		return (NULL);
	if (content && content_size)
	{
		if (!(new_list->content = (void*)malloc(content_size)))
		{
			free(new_list);
			return (NULL);
		}
		ft_memcpy(new_list->content, content, content_size);
		new_list->content_size = content_size;
		new_list->right = NULL;
		new_list->left = NULL;
	}
	else
	{
		new_list->content = NULL;
		new_list->content_size = 0;
		new_list->right = NULL;
		new_list->left = NULL;
	}
	return (new_list);
}
