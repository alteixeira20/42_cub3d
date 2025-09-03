/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:05 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/03 19:58:39 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_blocked(t_map *m, double y, double x)
{
	int	tx;
	int	ty;

	tx = (int)x;
	ty = (int)y;
	if (tx < 0 || ty < 0 || tx >= m->width || ty >= m->height)
		return (1);
	return (m->grid[ty][tx] == '1');
}

static void	move_lr(t_game *cube, double ny, double nx, double ms)
{
	if (cube->inp.left)
	{
		if (!is_blocked(&cube->map, ny, nx - cube->player.plane_x * ms))
			cube->player.pos_x -= cube->player.plane_x * ms;
		if (!is_blocked(&cube->map, ny - cube->player.plane_y * ms, nx))
			cube->player.pos_y -= cube->player.plane_y * ms;
	}
	if (cube->inp.right)
	{
		if (!is_blocked(&cube->map, ny, nx + cube->player.plane_x * ms))
			cube->player.pos_x += cube->player.plane_x * ms;
		if (!is_blocked(&cube->map, ny + cube->player.plane_y * ms, nx))
			cube->player.pos_y += cube->player.plane_y * ms;
	}
}

static void	move_fb(t_game *cube, double ny, double nx, double ms)
{
	if (cube->inp.forward)
	{
		if (!is_blocked(&cube->map, ny, nx + cube->player.dir_x * ms))
			cube->player.pos_x += cube->player.dir_x * ms;
		if (!is_blocked(&cube->map, ny + cube->player.dir_y * ms, nx))
			cube->player.pos_y += cube->player.dir_y * ms;
	}
	if (cube->inp.backward)
	{
		if (!is_blocked(&cube->map, ny, nx - cube->player.dir_x * ms))
			cube->player.pos_x -= cube->player.dir_x * ms;
		if (!is_blocked(&cube->map, ny - cube->player.dir_y * ms, nx))
			cube->player.pos_y -= cube->player.dir_y * ms;
	}
}

static void	move_strafe(t_game *cube, double ms)
{
	double	nx;
	double	ny;

	nx = cube->player.pos_x;
	ny = cube->player.pos_y;
	move_fb(cube, ny, nx, ms);
	move_lr(cube, ny, nx, ms);
}

void	update_player(t_game *cube)
{
	double	ms;
	double	rs;
	double	old_dir_x;
	double	old_plane_x;

	ms = 0.07;
	rs = 0.05;
	old_dir_x = cube->player.dir_x;
	old_plane_x = cube->player.plane_x;
	if (cube->inp.turn_l)
		rotate_left(cube, old_dir_x, old_plane_x, rs);
	if (cube->inp.turn_r)
		rotate_right(cube, old_dir_x, old_plane_x, rs);
	move_strafe(cube, ms);
}
