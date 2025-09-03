/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:05 by jopedro-          #+#    #+#             */
/*   Updated: 2025/08/13 16:15:09 by jopedro-         ###   ########.fr       */
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

static void	move_strafe(t_game *cube, double ms)
{
	double	nx;
	double	ny;

	nx = cube->player.pos_x;
	ny = cube->player.pos_y;
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

static void	rotate_lr(t_game *cube, double rs)
{
	double	old_dir_x;
	double	old_plane_x;

	if (cube->inp.turn_l)
	{
		old_dir_x = cube->player.dir_x;
		old_plane_x = cube->player.plane_x;
		cube->player.dir_x = cube->player.dir_x * cos(-rs)
			- cube->player.dir_y * sin(-rs);
		cube->player.dir_y = old_dir_x * sin(-rs)
			+ cube->player.dir_y * cos(-rs);
		cube->player.plane_x = cube->player.plane_x * cos(-rs)
			- cube->player.plane_y * sin(-rs);
		cube->player.plane_y = old_plane_x * sin(-rs)
			+ cube->player.plane_y * cos(-rs);
	}
	if (cube->inp.turn_r)
	{
		old_dir_x = cube->player.dir_x;
		old_plane_x = cube->player.plane_x;
		cube->player.dir_x = cube->player.dir_x * cos(rs)
			- cube->player.dir_y * sin(rs);
		cube->player.dir_y = old_dir_x * sin(rs)
			+ cube->player.dir_y * cos(rs);
		cube->player.plane_x = cube->player.plane_x * cos(rs)
			- cube->player.plane_y * sin(rs);
		cube->player.plane_y = old_plane_x * sin(rs)
			+ cube->player.plane_y * cos(rs);
	}
}

void	update_player(t_game *cube)
{
	double	ms;
	double	rs;

	ms = 0.07;
	rs = 0.05;
	move_strafe(cube, ms);
	rotate_lr(cube, rs);
}

