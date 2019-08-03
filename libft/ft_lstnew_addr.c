#include "libft.h"

t_list	*ft_lstnew_addr(void *content, size_t content_size)
{
	t_list	*new_list;

	if (!(new_list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content && content_size)
	{
		if (!(new_list->content = (void*)malloc(content_size)))
		{
			free(new_list);
			return (NULL);
		}
		new_list->content =  content;
		new_list->content_size = content_size;
		new_list->next = NULL;
	}
	else
	{
		new_list->content = NULL;
		new_list->content_size = 0;
		new_list->next = NULL;
	}
	return (new_list);
}