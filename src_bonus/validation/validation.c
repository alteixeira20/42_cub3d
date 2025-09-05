/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:38:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 19:02:10 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

int	validate_map_closed(t_game *game)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * game->map.height);
	if (!copy)
		return (print_error(ERR_ALLOC), -1);
	y = 0;
	while (y < game->map.height)
	{
		copy[y] = ft_strdup(game->map.grid[y]);
		if (!copy[y])
			return (print_error(ERR_ALLOC), -1);
		y++;
	}
	if (!flood_fill(copy, &game->map,
			(int)game->player.pos_x, (int)game->player.pos_y))
	{
		clean_str_array(copy, game->map.height);
		return (print_error(ERR_MAP_OPEN), -1);
	}
	clean_str_array(copy, game->map.height);
	return (0);
}
