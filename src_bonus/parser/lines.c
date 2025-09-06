/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 01:04:14 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 18:58:37 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

char	*line_dup_trimmed(const char *src)
{
	int		len;
	int		i;
	char	*dup;

	len = ft_strlen(src);
	if (len > 0 && src[len - 1] == '\n')
		len--;
	if (len > 0 && src[len - 1] == '\r')
		len--;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

int	lines_buf_init(t_map_buffer *buf, int capacity)
{
	buf->items = malloc(sizeof(char *) * capacity);
	if (!buf->items)
		return (print_error(ERR_ALLOC), -1);
	buf->count = 0;
	buf->capacity = capacity;
	return (0);
}

int	lines_buf_push(t_map_buffer *buf, const char *line)
{
	char	*copy;

	if (buf->count >= buf->capacity)
		return (print_error(ERR_ALLOC), -1);
	copy = line_dup_trimmed(line);
	if (!copy)
		return (print_error(ERR_ALLOC), -1);
	buf->items[buf->count] = copy;
	buf->count += 1;
	return (0);
}

static int	header_try_line(const char *line, t_game *g)
{
	int	start;

	start = 0;
	while (line[start] == ' ')
		start++;
	if (!ft_strncmp(line + start, ID_NO, 2) && (line[start + 2] == ' '
			|| line[start + 2] == '\t'))
		return (parse_texture(line + start, g));
	if (!ft_strncmp(line + start, ID_SO, 2) && (line[start + 2] == ' '
			|| line[start + 2] == '\t'))
		return (parse_texture(line + start, g));
	if (!ft_strncmp(line + start, ID_WE, 2) && (line[start + 2] == ' '
			|| line[start + 2] == '\t'))
		return (parse_texture(line + start, g));
	if (!ft_strncmp(line + start, ID_EA, 2) && (line[start + 2] == ' '
			|| line[start + 2] == '\t'))
		return (parse_texture(line + start, g));
	return (parse_color(line + start, g));
}

int	process_line(const char *line, int *in_map, t_game *game, t_map_buffer *buf)
{
	int	r;

	if (*in_map == 0)
	{
		if (line_is_spaces_only(line))
			return (0);
		r = header_try_line(line, game);
		if (r == 1)
			return (0);
		if (r == -1)
			return (-1);
		if (!line_is_map_content(line))
			return (print_error(ERR_INVALID_ID), -1);
		if (!ids_complete(game))
			return (print_error(ERR_MISSING_ID), -1);
		if (lines_buf_push(buf, line) != 0)
			return (-1);
		*in_map = 1;
		return (0);
	}
	if (line_is_spaces_only(line))
		return (print_error(ERR_MAP_EMPTY_LINE), -1);
	if (!line_is_map_content(line))
		return (print_error(ERR_MAP_CHAR), -1);
	return (lines_buf_push(buf, line));
}
