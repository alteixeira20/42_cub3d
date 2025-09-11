/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:30:07 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 18:11:34 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	process_and_validate_line(char *raw, int *in_map, t_parser_ctx *ctx)
{
	char	*trimmed;
	int		status;

	trimmed = line_dup_trimmed(raw);
	if (!trimmed)
	{
		close(ctx->fd);
		clean_map_buffer(ctx->buf);
		return (print_error(ERR_ALLOC), -1);
	}
	free(raw);
	status = process_line(trimmed, in_map, ctx->game, ctx->buf);
	free(trimmed);
	if (status != 0)
	{
		close(ctx->fd);
		clean_map_buffer(ctx->buf);
		return (-1);
	}
	return (0);
}

static int	read_and_process_lines(int fd, int *in_map,
									t_game *cube, t_map_buffer *buf)
{
	t_parser_ctx	ctx;
	char			*line;

	ctx.fd = fd;
	ctx.game = cube;
	ctx.buf = buf;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (process_and_validate_line(line, in_map, &ctx) != 0)
		{
			line = get_next_line(-1);
			return (-1);
		}
	}
	line = get_next_line(-1);
	return (0);
}

int	parse_all(const char *path, t_game *cube, int in_map)
{
	t_map_buffer	buf;
	int				fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_CANNOT_OPEN), -1);
	if (lines_buf_init(&buf, 1024) != 0)
		return (close(fd), -1);
	if (read_and_process_lines(fd, &in_map, cube, &buf) != 0)
		return (clean_map_buffer(&buf), -1);
	close(fd);
	if (!in_map)
		return (clean_map_buffer(&buf), print_error(ERR_MISSING_ID), -1);
	if (parse_map(buf.items, buf.count, &cube->map) != 0)
		return (clean_map_buffer(&buf), -1);
	parse_doors(cube);
	clean_map_buffer(&buf);
	if (parse_player(cube) != 0)
		return (-1);
	if (parse_collectibles(cube) != 0)
		return (-1);
	if (validate_map_closed(cube) != 0)
		return (-1);
	return (0);
}
