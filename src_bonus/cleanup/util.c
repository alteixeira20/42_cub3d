/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:50:55 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 19:19:52 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	clean_texture(t_texture *t)
{
	if (t->path)
	{
		free(t->path);
		t->path = NULL;
	}
	t->is_set = false;
}

void	clean_map(t_map *m)
{
	int	y;

	if (!m->grid)
		return ;
	y = 0;
	while (y < m->height)
	{
		free(m->grid[y]);
		y++;
	}
	free(m->grid);
	m->grid = NULL;
	m->width = 0;
	m->height = 0;
}

static void	free_collectibles_array(t_game *cube)
{
	if (cube->collect.items)
	{
		free(cube->collect.items);
		cube->collect.items = NULL;
		cube->collect.count = 0;
		cube->collect.collected = 0;
	}
}

void	clean_keys(t_game *cube)
{
	int	i;

	free_collectibles_array(cube);
	i = 0;
	while (i < KEY_FRAME_COUNT)
	{
		if (cube->collect.key_frames[i].img)
		{
			mlx_destroy_image(cube->render.mlx,
				cube->collect.key_frames[i].img);
			cube->collect.key_frames[i].img = NULL;
			cube->collect.key_frames[i].addr = NULL;
			cube->collect.key_frames[i].w = 0;
			cube->collect.key_frames[i].h = 0;
			cube->collect.key_frames[i].bpp = 0;
			cube->collect.key_frames[i].line_len = 0;
			cube->collect.key_frames[i].endian = 0;
		}
		i = i + 1;
	}
}
