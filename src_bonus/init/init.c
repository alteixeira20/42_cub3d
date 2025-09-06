/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:23:11 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 20:51:33 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	color_init(t_color *c)
{
	c->r = 0;
	c->g = 0;
	c->b = 0;
	c->argb = 0;
	c->is_set = false;
}

static void	map_init(t_map *m)
{
	m->grid = NULL;
	m->width = 0;
	m->height = 0;
}

static void	player_init(t_player *p)
{
	p->tile_x = 0;
	p->tile_y = 0;
	p->pos_x = 0.0;
	p->pos_y = 0.0;
	p->dir_x = 0.0;
	p->dir_y = -1.0;
	p->plane_x = 0.66;
	p->plane_y = 0.0;
	p->pitch = 0.0;
	p->dir_char = 'N';
	p->is_set = false;
}

static void	texture_init(t_texture *t)
{
	t->path = NULL;
	t->is_set = false;
}

void	game_init(t_game *game)
{
	texture_init(&game->tex_no);
	texture_init(&game->tex_so);
	texture_init(&game->tex_we);
	texture_init(&game->tex_ea);
	color_init(&game->floor_color);
	color_init(&game->ceil_color);
	map_init(&game->map);
	input_init(&game->inp);
	player_init(&game->player);
	game->paused = false;
}
