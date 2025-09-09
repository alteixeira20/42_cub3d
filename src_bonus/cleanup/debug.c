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

#include "../../inc/cub3d_bonus.h"

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

void	print_parse(const t_game *cube)
{
	print_str_field("North texture path: ", cube->tex_no.path);
	print_str_field("South texture path: ", cube->tex_so.path);
	print_str_field("East texture path: ", cube->tex_ea.path);
	print_str_field("West texture path: ", cube->tex_we.path);
	ft_printf("Floor RGB: %d, %d, %d  ARGB: %u\n",
		cube->floor_color.r, cube->floor_color.g,
		cube->floor_color.b, cube->floor_color.argb);
	ft_printf("Ceiling RGB: %d, %d, %d  ARGB: %u\n",
		cube->ceil_color.r, cube->ceil_color.g,
		cube->ceil_color.b, cube->ceil_color.argb);
	print_int_field("Map width: ", cube->map.width);
	print_int_field("Map height: ", cube->map.height);
	print_grid(cube->map.grid, cube->map.height);
	print_int_field("Player Tile X: ", cube->player.tile_x);
	print_int_field("Player Tile Y: ", cube->player.tile_y);
	print_double_field("Player Pos X: ", cube->player.pos_x);
	print_double_field("Player Pos Y: ", cube->player.pos_y);
	ft_printf("Player Direction: %c\n", cube->player.dir_char);
	ft_printf("Dir vector: (%.2f, %.2f)\n", cube->player.dir_x,
		cube->player.dir_y);
	ft_printf("Plane vector: (%.2f, %.2f)\n", cube->player.plane_x,
		cube->player.plane_y);
}
