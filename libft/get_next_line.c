/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drdraugr <variya1@yandex.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 19:20:38 by drdraugr          #+#    #+#             */
/*   Updated: 2019/07/31 17:19:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_line(char **prev)
{
	char	*line_break;
	char	*line;

	line = NULL;
	line_break = ft_strchr(*prev, '\n');
	if (line_break == NULL)
		return (line);
	line = ft_strnew(line_break - *prev);
	line = ft_strncpy(line, *prev, line_break - *prev);
	line_break = ft_strdup(line_break + 1);
	ft_strdel(prev);
	*prev = line_break;
	return (line);
}

char	*find_tail(char **prev)
{
	char	*line;

	line = NULL;
	if (ft_strlen(*prev) != 0 && !ft_strchr(*prev, '\n'))
	{
		line = ft_strdup(*prev);
		ft_strdel(prev);
	}
	return (line);
}

int		get_next_line(const int fd, char **line)
{
	static char		*prev[4864];
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if (fd < 0 || read(fd, buff, 0) < 0 || line == NULL)
		return (-1);
	if (prev[fd] == NULL)
		prev[fd] = ft_strnew(0);
	while (1)
	{
		if ((*line = find_line(&prev[fd])) && *line)
			return (1);
		ret = read(fd, buff, BUFF_SIZE);
		buff[ret] = '\0';
		tmp = ft_strjoin(prev[fd], buff);
		free(prev[fd]);
		prev[fd] = tmp;
		if (ret == 0)
		{
			if ((*line = find_tail(&prev[fd])) && *line)
				return (1);
			return (0);
		}
	}
}
