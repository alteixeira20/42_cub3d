/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:19:56 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 19:29:28 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	create_minimap_image(t_game *cube, t_minimap *m)
{
	m->img_ptr = mlx_new_image(cube->render.mlx, m->width, m->height);
	if (!m->img_ptr)
	{
		print_error("Failed to create minimap image");
		clean_game(cube);
	}
	m->addr = mlx_get_data_addr(m->img_ptr, &m->bpp, &m->line_len, &m->endian);
	if (!m->addr)
	{
		print_error("Failed to create minimap data address");
		clean_game(cube);
	}
}

void	minimap_init(t_game *cube)
{
	t_minimap	*minimap;

	minimap = &cube->minimap;
	minimap->tile_size = MM_TILE_SIZE;
	minimap->radius_tiles = MM_RADIUS_TILES;
	minimap->width = (minimap->radius_tiles * 2 + 1) * minimap->tile_size;
	minimap->height = minimap->width;
	minimap->offset_x = SCR_W - minimap->width - MM_OFFSET_MARGIN;
	minimap->offset_y = MM_OFFSET_MARGIN;
	minimap->scale = MM_SCALE;
	minimap->enabled = true;
	minimap->img_ptr = NULL;
	minimap->addr = NULL;
	minimap->bpp = 0;
	minimap->line_len = 0;
	minimap->endian = 0;
	create_minimap_image(cube, minimap);
}
