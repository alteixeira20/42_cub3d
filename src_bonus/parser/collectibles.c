/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:40:00 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 19:42:08 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	count_collectibles(const t_map *m)
{
	int	x;
	int	y;
	int	cnt;

	cnt = 0;
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->grid[y][x] == 'C')
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

static void	assign_collectable(t_game *cube, int y)
{
	int	i;
	int	x;

	i = 0;
	while (y < cube->map.height)
	{
		x = 0;
		while (x < cube->map.width)
		{
			if (cube->map.grid[y][x] == 'C')
			{
				cube->collect.items[i].tile_x = x;
				cube->collect.items[i].tile_y = y;
				cube->collect.items[i].pos_x = x + 0.5;
				cube->collect.items[i].pos_y = y + 0.5;
				cube->collect.items[i].collected = 0;
				cube->collect.items[i].phase = (double)
					((x * 31 + y * 17) % 100) / 100.0;
				i++;
			}
			x++;
		}
		y++;
	}
}

int	parse_collectibles(t_game *cube)
{
	int	y;
	int	total;

	total = count_collectibles(&cube->map);
	cube->collect.count = total;
	cube->collect.collected = 0;
	cube->collect.anim_t = 0.0;
	cube->collect.items = NULL;
	if (total <= 0)
		return (0);
	cube->collect.items = (t_collectible *)
		malloc(sizeof(t_collectible) * total);
	if (!cube->collect.items)
		return (print_error(ERR_ALLOC), -1);
	y = 0;
	assign_collectable(cube, y);
	return (0);
}
