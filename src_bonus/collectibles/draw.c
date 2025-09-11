/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:14:57 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 18:05:39 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	draw_stripe(t_drawctx *d, t_bounds *b, int stripe, int tex_x)
{
	int				y;
	int				d_y;
	int				tex_y;
	unsigned int	col;

	if (d->ty >= d->cube->zbuf[stripe])
		return ;
	y = b->start_y;
	while (y <= b->end_y)
	{
		d_y = y - b->start_y;
		tex_y = (int)(
				(double)d_y * d->tex->h / (double)(b->end_y - b->start_y + 1));
		col = get_texel(d->tex, tex_x, tex_y);
		if (col != d->trans)
			put_pixel_img(&d->cube->render.frame, stripe, y, col);
		y = y + 1;
	}
}

static void	draw_sprite_body(t_drawctx *d, t_bounds *b)
{
	int	stripe;
	int	tex_x;
	int	span;

	stripe = b->start_x;
	span = b->end_x - b->start_x + 1;
	while (stripe <= b->end_x)
	{
		tex_x = (int)((double)(stripe - b->start_x) * d->tex->w / (double)span);
		draw_stripe(d, b, stripe, tex_x);
		stripe = stripe + 1;
	}
}

static void	draw_one(t_game *cube, t_collectible *c,
						t_img *tex, unsigned int trans)
{
	double		coord[2];
	int			vars[4];
	t_bounds	b;
	t_drawctx	d;

	coord[0] = 0.0;
	coord[1] = 0.0;
	sprite_transform(cube, c, &coord[0], &coord[1]);
	if (coord[1] <= 0.001)
		return ;
	vars[0] = (int)((SCR_W / 2.0) * (1.0 + coord[0] / coord[1]));
	vars[1] = (int)fabs((double)SCR_H / coord[1] * KEY_SCALE);
	vars[2] = vars[1];
	vars[3] = (int)(-cube->player.pitch * SCR_H)
		+ (int)(sin(cube->collect.anim_t * 2.0 + c->phase) * KEY_BOB_AMP_PX);
	b = sprite_bounds(vars[0], vars[2], vars[1], vars[3]);
	d.cube = cube;
	d.tex = tex;
	d.trans = trans;
	d.ty = coord[1];
	draw_sprite_body(&d, &b);
}

void	collectibles_draw(t_game *cube)
{
	int				i;
	int				frame_idx;
	t_img			*tex;
	unsigned int	trans;

	if (cube->collect.count <= 0 || !cube->collect.items)
		return ;
	frame_idx = (int)(cube->collect.anim_t * KEY_ANIM_FPS) % KEY_FRAME_COUNT;
	tex = &cube->collect.key_frames[frame_idx];
	trans = get_texel(tex, 0, 0);
	i = 0;
	while (i < cube->collect.count)
	{
		if (!cube->collect.items[i].collected)
			draw_one(cube, &cube->collect.items[i], tex, trans);
		i = i + 1;
	}
}
