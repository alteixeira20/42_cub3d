/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:38:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 16:24:11 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	has_cub_extension(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 4)
		return (0);
	if (str[i - 4] != '.')
		return (0);
	i -= 3;
	if (ft_strncmp(&str[i], "cub", 3) != 0)
		return (0);
	return (1);
}

int	has_xpm_extension(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	if (i < 4)
		return (0);
	if (str[i - 4] != '.')
		return (0);
	i -= 3;
	if (ft_strncmp(&str[i], "xpm", 3) != 0)
		return (0);
	return (1);
}

static int	flood_fill(char **grid, t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'F')
		return (1);
	if (grid[y][x] == ' ')
		return (0);
	grid[y][x] = 'F';
	if (!flood_fill(grid, map, x + 1, y))
		return (0);
	if (!flood_fill(grid, map, x - 1, y))
		return (0);
	if (!flood_fill(grid, map, x, y + 1))
		return (0);
	if (!flood_fill(grid, map, x, y - 1))
		return (0);
	return (1);
}

int	validate_map_closed(t_game *cube)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * cube->map.height);
	if (!copy)
		return (print_error(ERR_ALLOC), -1);
	y = 0;
	while (y < cube->map.height)
	{
		copy[y] = ft_strdup(cube->map.grid[y]);
		if (!copy[y])
			return (print_error(ERR_ALLOC), -1);
		y++;
	}
	if (!flood_fill(copy, &cube->map,
			(int)cube->player.pos_x, (int)cube->player.pos_y))
	{
		clean_str_array(copy, cube->map.height);
		return (print_error(ERR_MAP_OPEN), -1);
	}
	clean_str_array(copy, cube->map.height);
	return (0);
}

int	validate_no_adjacent_doors(const t_game *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < cube->map.height)
	{
		x = 0;
		while (x < cube->map.width)
		{
			if (cube->map.grid[y][x] == 'D')
			{
				if (x + 1 < cube->map.width && cube->map.grid[y][x + 1] == 'D')
					return (print_error(ERR_DOORS_ADJACENT), -1);
				if (y + 1 < cube->map.height && cube->map.grid[y + 1][x] == 'D')
					return (print_error(ERR_DOORS_ADJACENT), -1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
