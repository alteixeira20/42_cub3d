/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:29:58 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/03 17:25:08 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	clean_texture(t_texture *t)
{
	if (t->path)
	{
		free(t->path);
		t->path = NULL;
	}
	t->is_set = false;
}

static void	clean_map(t_map *m)
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

void	clean_game(t_game *game)
{
	clean_texture(&game->tex_no);
	clean_texture(&game->tex_so);
	clean_texture(&game->tex_we);
	clean_texture(&game->tex_ea);
	clean_map(&game->map);
	game->floor_color.is_set = false;
	game->ceil_color.is_set = false;
	game->player.is_set = false;
	textures_destroy(game);
	render_destroy(game);
}

void	clean_map_buffer(t_map_buffer *buf)
{
	int	i;

	i = 0;
	while (i < buf->count)
	{
		free(buf->items[i]);
		i++;
	}
	free(buf->items);
	buf->items = NULL;
	buf->count = 0;
	buf->capacity = 0;
}

void	clean_str_array(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
