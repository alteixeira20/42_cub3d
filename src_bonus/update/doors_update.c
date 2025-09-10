/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:09:13 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/10 13:57:37 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static float	dist_sq(float ax, float ay, float bx, float by)
{
	float	dx;
	float	dy;

	dx = ax - bx;
	dy = ay - by;
	return (dx * dx + dy * dy);
}

static void	update_one(t_door *d, t_vec2 p)
{
	float	cx;
	float	cy;
	float	r2;

	cx = (float)d->grid_x + 0.5f;
	cy = (float)d->grid_y + 0.5f;
	r2 = DOOR_RADIUS * DOOR_RADIUS;
	if (dist_sq(p.x, p.y, cx, cy) <= r2)
		d->opening = 1;
	else
		d->opening = 0;
	if (d->opening && d->open_t < 1.0f)
	{
		d->open_t += DOOR_OPEN_SPEED;
		if (d->open_t > 1.0f)
			d->open_t = 1.0f;
	}
	if (!d->opening && d->open_t > 0.0f)
	{
		d->open_t -= DOOR_OPEN_SPEED;
		if (d->open_t < 0.0f)
			d->open_t = 0.0f;
	}
}

void	doors_update(t_doors *doors, char **map, t_vec2 p)
{
	size_t	i;

	(void)map;
	i = 0;
	while (i < doors->len)
	{
		update_one(&doors->arr[i], p);
		i++;
	}
}

void	update_doors_for_frame(t_game *cube)
{
	t_vec2	p;

	p.x = (float)cube->player.pos_x;
	p.y = (float)cube->player.pos_y;
	doors_update(&cube->doors, cube->map.grid, p);
}
