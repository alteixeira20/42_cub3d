/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:05 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/10 13:58:21 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	is_blocked(t_map *m, double y, double x)
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;

	x0 = (int)floor(x - COLL_R);
	x1 = (int)floor(x + COLL_R);
	y0 = (int)floor(y - COLL_R);
	y1 = (int)floor(y + COLL_R);
	if (x0 < 0 || y0 < 0 || x1 >= m->width || y1 >= m->height)
		return (1);
	return (m->grid[y0][x0] == '1' || m->grid[y0][x1] == '1'
		|| m->grid[y1][x0] == '1' || m->grid[y1][x1] == '1');
}

static void	get_movement_vector(t_game *c, double *dx, double *dy)
{
	if (c->inp.forward)
	{
		*dx += c->player.dir_x;
		*dy += c->player.dir_y;
	}
	if (c->inp.backward)
	{
		*dx -= c->player.dir_x;
		*dy -= c->player.dir_y;
	}
	if (c->inp.left)
	{
		*dx -= c->player.plane_x;
		*dy -= c->player.plane_y;
	}
	if (c->inp.right)
	{
		*dx += c->player.plane_x;
		*dy += c->player.plane_y;
	}
}

static void	move_combined(t_game *c, double ms)
{
	double	dx;
	double	dy;
	double	len;

	dx = 0.0;
	dy = 0.0;
	get_movement_vector(c, &dx, &dy);
	len = sqrt((dx * dx) + (dy * dy));
	if (len > 0.0001)
	{
		dx = (dx / len) * ms;
		dy = (dy / len) * ms;
		if (!is_blocked(&c->map, c->player.pos_y, c->player.pos_x + dx))
			c->player.pos_x += dx;
		if (!is_blocked(&c->map, c->player.pos_y + dy, c->player.pos_x))
			c->player.pos_y += dy;
	}
}

void	update_player(t_game *cube)
{
	double			ms;

	update_mouse_angle(cube);
	apply_mouse_yaw(cube);
	apply_mouse_pitch(cube);
	ms = 0.1;
	move_combined(cube, ms);
	collectibles_update(cube);
}
