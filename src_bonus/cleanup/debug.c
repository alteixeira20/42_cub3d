/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:01:02 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 18:57:58 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	print_str_field(const char *label, const char *value)
{
	if (value)
		ft_printf("%s%s\n", label, value);
	else
		ft_printf("%s(null)\n", label);
}

static void	print_int_field(const char *label, int value)
{
	ft_printf("%s%d\n", label, value);
}

static void	print_double_field(const char *label, double value)
{
	ft_printf("%s%.2f\n", label, value);
}

void	print_grid(char **map, int height)
{
	int	i;

	ft_printf("Map grid:\n");
	i = 0;
	while (i < height)
	{
		if (map[i])
			ft_printf("%s\n", map[i]);
		i++;
	}
}

void	print_parse(const t_game *game)
{
	print_str_field("North texture path: ", game->tex_no.path);
	print_str_field("South texture path: ", game->tex_so.path);
	print_str_field("East texture path: ", game->tex_ea.path);
	print_str_field("West texture path: ", game->tex_we.path);
	ft_printf("Floor RGB: %d, %d, %d  ARGB: %u\n",
		game->floor_color.r, game->floor_color.g,
		game->floor_color.b, game->floor_color.argb);
	ft_printf("Ceiling RGB: %d, %d, %d  ARGB: %u\n",
		game->ceil_color.r, game->ceil_color.g,
		game->ceil_color.b, game->ceil_color.argb);
	print_int_field("Map width: ", game->map.width);
	print_int_field("Map height: ", game->map.height);
	print_grid(game->map.grid, game->map.height);
	print_int_field("Player Tile X: ", game->player.tile_x);
	print_int_field("Player Tile Y: ", game->player.tile_y);
	print_double_field("Player Pos X: ", game->player.pos_x);
	print_double_field("Player Pos Y: ", game->player.pos_y);
	ft_printf("Player Direction: %c\n", game->player.dir_char);
	ft_printf("Dir vector: (%.2f, %.2f)\n", game->player.dir_x,
		game->player.dir_y);
	ft_printf("Plane vector: (%.2f, %.2f)\n", game->player.plane_x,
		game->player.plane_y);
}
