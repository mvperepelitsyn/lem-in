/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:49:33 by uhand             #+#    #+#             */
/*   Updated: 2019/01/07 18:49:36 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	add_buff(char **prev_buf, char *new_content)
{
	char		*temp_buf;

	if (!(temp_buf = ft_strjoin(*prev_buf, new_content)))
		return (-1);
	if (*prev_buf != NULL)
		free(*prev_buf);
	*prev_buf = temp_buf;
	return (1);
}

static int	trim_buf(char **current_buf, size_t trim_size)
{
	char		*temp_buf;
	size_t		i;

	i = ft_strlen(*current_buf);
	if (trim_size >= i)
	{
		ft_strdel(current_buf);
		return (1);
	}
	if (!(temp_buf = ft_strnew(i - trim_size)))
		return (-1);
	i = 0;
	while (current_buf[0][trim_size + i] != '\0')
	{
		temp_buf[i] = current_buf[0][trim_size + i];
		i++;
	}
	free(*current_buf);
	*current_buf = temp_buf;
	return (1);
}

static int	make_line(char **addr, char **current_buf, size_t split_ind)
{
	size_t		i;

	if (*current_buf == NULL || !ft_strlen(*current_buf))
		return (0);
	if (split_ind == 0)
	{
		if (!trim_buf(current_buf, 1))
			return (-1);
		*addr = ft_strnew(0);
		return (1);
	}
	if (!(addr[0] = ft_strnew(split_ind)))
		return (-1);
	i = 0;
	while (i < split_ind)
	{
		addr[0][i] = current_buf[0][i];
		i++;
	}
	if (!trim_buf(current_buf, split_ind + 1))
		return (-1);
	return (1);
}

static int	check_prev_buf(char **addr, char **prev_buf, size_t *i)
{
	if (*prev_buf == NULL)
		return (0);
	while (prev_buf[0][*i] != '\0')
	{
		if (prev_buf[0][*i] == SPLITTER)
			return (make_line(addr, prev_buf, *i));
		*i = *i + 1;
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*fd_ind[MAX_OPEN];
	int			result;
	int			read_size;
	char		buf[BUFF_SIZE + 1];
	size_t		i;

	if (fd < 0 || line == NULL || fd > MAX_OPEN)
		return (-1);
	i = 0;
	while ((result = check_prev_buf(line, &fd_ind[fd], &i)) == 0)
	{
		if ((read_size = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if (read_size == 0)
			return (make_line(line, &fd_ind[fd], i));
		buf[read_size] = '\0';
		if (!(add_buff(&fd_ind[fd], buf)))
			return (-1);
	}
	return (result);
}
