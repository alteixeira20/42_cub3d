/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:17:29 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 18:05:30 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	sprite_transform(t_game *cube, t_collectible *c,
								double *tx, double *ty)
{
	double	sx;
	double	sy;
	double	inv;

	sx = c->pos_x - cube->player.pos_x;
	sy = c->pos_y - cube->player.pos_y;
	inv = 1.0 / (cube->player.plane_x * cube->player.dir_y
			- cube->player.dir_x * cube->player.plane_y);
	*tx = inv * (cube->player.dir_y * sx - cube->player.dir_x * sy);
	*ty = inv * (-cube->player.plane_y * sx + cube->player.plane_x * sy);
}

t_bounds	sprite_bounds(int screen_x,
							int sprite_w, int sprite_h, int v_off)
{
	t_bounds	b;
	int			y0;
	int			x0;

	y0 = -sprite_h / 2 + SCR_H / 2 + v_off;
	x0 = -sprite_w / 2 + screen_x;
	b.start_y = clampi(y0, 0, SCR_H - 1);
	b.end_y = clampi(y0 + sprite_h - 1, 0, SCR_H - 1);
	b.start_x = clampi(x0, 0, SCR_W - 1);
	b.end_x = clampi(x0 + sprite_w - 1, 0, SCR_W - 1);
	return (b);
}

int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}
