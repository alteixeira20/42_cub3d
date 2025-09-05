/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:05 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/04 17:27:20 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
		*dx = *dx + c->player.dir_x;
		*dy = *dy + c->player.dir_y;
	}
	if (c->inp.backward)
	{
		*dx = *dx - c->player.dir_x;
		*dy = *dy - c->player.dir_y;
	}
	if (c->inp.left)
	{
		*dx = *dx - c->player.plane_x;
		*dy = *dy - c->player.plane_y;
	}
	if (c->inp.right)
	{
		*dx = *dx + c->player.plane_x;
		*dy = *dy + c->player.plane_y;
	}
}

static void	move_combined(t_game *cube, double ms)
{
	double	dx;
	double	dy;
	double	len;

	dx = 0;
	dy = 0;
	get_movement_vector(cube, &dx, &dy);
	len = sqrt((dx * dx) + (dy * dy));
	if (len > 0.0001)
	{
		dx = dx / len * ms;
		dy = dy / len * ms;
		if (!is_blocked(&cube->map, cube->player.pos_y,
				cube->player.pos_x + dx))
			cube->player.pos_x = cube->player.pos_x + dx;
		if (!is_blocked(&cube->map, cube->player.pos_y + dy,
				cube->player.pos_x))
			cube->player.pos_y = cube->player.pos_y + dy;
	}
}

void	update_player(t_game *cube)
{
	double	ms;
	double	rs;
	double	old_dir_x;
	double	old_plane_x;

	ms = 0.07;
	rs = 0.05;
	if (cube->inp.mouse_angle != 0.0)
	{
		rotate_angle(cube, cube->inp.mouse_angle);
		cube->inp.mouse_angle = 0.0;
	}
	old_dir_x = cube->player.dir_x;
	old_plane_x = cube->player.plane_x;

	move_combined(cube, ms);
}
