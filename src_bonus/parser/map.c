/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:09:35 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 16:06:01 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	map_calc_dims(char **lines, int count, int *out_w, int *out_h)
{
	int	i;
	int	w;
	int	len;

	w = 0;
	i = 0;
	while (i < count)
	{
		len = ft_strlen(lines[i]);
		if (len > w)
			w = len;
		i++;
	}
	*out_w = w;
	*out_h = count;
}

static void	map_free_rows_partial(t_map *map, int upto)
{
	int	y;

	y = 0;
	while (y < upto)
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

static int	map_alloc_grid(t_map *map, int width, int height)
{
	int	y;

	map->grid = malloc(sizeof(char *) * height);
	if (!map->grid)
		return (print_error(ERR_ALLOC), -1);
	y = 0;
	while (y < height)
	{
		map->grid[y] = malloc(sizeof(char) * width + 1);
		if (!map->grid[y])
		{
			print_error(ERR_ALLOC);
			map_free_rows_partial(map, y);
			return (-1);
		}
		map->grid[y][width] = '\0';
		y++;
	}
	map->width = width;
	map->height = height;
	return (0);
}

static void	map_copy_row_padded(char *dst, const char *src, int width)
{
	int	i;
	int	len;

	len = ft_strlen(src);
	i = 0;
	while (i < width)
	{
		if (i < len)
			dst[i] = src[i];
		else
			dst[i] = ' ';
		i++;
	}
}

int	parse_map(char **lines, int count, t_map *map)
{
	int	y;

	map_calc_dims(lines, count, &map->width, &map->height);
	if (map->width == 0 || map->height == 0)
		return (print_error(ERR_MAP_CHAR), -1);
	if (map_alloc_grid(map, map->width, map->height) != 0)
		return (-1);
	y = 0;
	while (y < map->height)
	{
		if (!lines[y])
			return (map_free_rows_partial(map, y), print_error(ERR_ALLOC), -1);
		map_copy_row_padded(map->grid[y], lines[y], map->width);
		y++;
	}
	return (0);
}
