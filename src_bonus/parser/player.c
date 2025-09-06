/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:06:14 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 16:23:32 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	is_player_char(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	return (0);
}

static int	assign_player(t_game *game, int x, int y, int *found)
{
	if (*found != 0)
		return (print_error(ERR_PLAYER_MULTI), -1);
	*found = 1;
	game->player.tile_x = x;
	game->player.tile_y = y;
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	set_dir_and_plane(game, game->map.grid[y][x]);
	game->player.is_set = true;
	game->map.grid[y][x] = '0';
	return (0);
}

static int	scan_row(t_game *game, int y, int *found)
{
	int		x;
	char	c;

	x = 0;
	while (x < game->map.width)
	{
		c = game->map.grid[y][x];
		if (is_player_char(c))
		{
			if (assign_player(game, x, y, found) != 0)
				return (-1);
		}
		x++;
	}
	return (0);
}

int	parse_player(t_game *game)
{
	int	y;
	int	found;

	y = 0;
	found = 0;
	while (y < game->map.height)
	{
		if (scan_row(game, y, &found) != 0)
			return (-1);
		y++;
	}
	if (found == 0)
		return (print_error(ERR_PLAYER_MISSING), -1);
	return (0);
}
