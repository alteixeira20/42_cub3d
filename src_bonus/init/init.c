/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:23:11 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 19:05:11 by paalexan         ###   ########.fr       */
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

void	game_init(t_game *cube)
{
	texture_init(&cube->tex_no);
	texture_init(&cube->tex_so);
	texture_init(&cube->tex_we);
	texture_init(&cube->tex_ea);
	texture_init(&cube->tex_do);
	color_init(&cube->floor_color);
	color_init(&cube->ceil_color);
	map_init(&cube->map);
	input_init(&cube->inp);
	player_init(&cube->player);
	render_init(cube);
	tex_rt_init(cube);
	cube->doors.arr = NULL;
	cube->doors.len = 0;
	cube->paused = false;
	cube->collect.items = NULL;
	cube->collect.count = 0;
	cube->collect.collected = 0;
	cube->collect.anim_t = 0.0;
	keys_init(cube);
}
