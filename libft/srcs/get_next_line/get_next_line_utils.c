/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:30:27 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 20:29:11 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	increase_line(char **new, char **old, int *old_size, int inc_size)
{
	*new = malloc(sizeof(*new) * (*old_size + inc_size + 1));
	if (!*new)
	{
		if (*old)
			ft_free_set_null(old);
		return (0);
	}
	return (1);
}

static int	gnl_strncat(char *buf, char **line, int *old_size, int inc_size)
{
	char	*new_line;

	if (!increase_line(&new_line, line, old_size, inc_size))
		return (0);
	if (*line)
	{
		ft_memcpy(new_line, *line, *old_size);
		free(*line);
	}
	ft_memcpy(&new_line[*old_size], buf, inc_size);
	*old_size += inc_size;
	new_line[*old_size] = '\0';
	*line = new_line;
	return (1);
}

static void	buffer_clean(char *buf, int pivot)
{
	int	i;

	i = 0;
	while (buf[pivot] && pivot < BUFFER_SIZE)
		buf[i++] = buf[pivot++];
	buf[i] = '\0';
}

int	buffer_to_line(char *buf, char **line, int *line_len)
{
	int	i;
	int	stop;

	if (!*buf)
		return (0);
	stop = 0;
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		stop = 1;
	if (!gnl_strncat(buf, line, line_len, i + stop))
		stop = 1;
	buffer_clean(buf, i + 1);
	return (stop);
}

int	buffer_refill(int fd, char *buf, char **line)
{
	int	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes < 0)
	{
		buf[0] = '\0';
		if (*line)
			ft_free_set_null(line);
		return (0);
	}
	buf[bytes] = '\0';
	if (!bytes)
		return (0);
	return (1);
}
