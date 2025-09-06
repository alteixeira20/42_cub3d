/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:31:05 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/06 12:01:56 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	apply_mouse_yaw(t_game *cube)
{
	double	ang;

	ang = cube->inp.mouse_angle;
	if (ang != 0.0)
	{
		rotate_player(cube, ang);
		cube->inp.mouse_angle = 0.0;
	}
}

void	apply_mouse_pitch(t_game *cube)
{
	double	dy;

	dy = cube->inp.mouse_dy;
	if (dy != 0.0)
	{
		cube->player.pitch += dy * cube->inp.sens;
		if (cube->player.pitch > 0.5)
			cube->player.pitch = 0.5;
		if (cube->player.pitch < -0.5)
			cube->player.pitch = -0.5;
		cube->inp.mouse_dy = 0.0;
	}
}

void	update_mouse_angle(t_game *cube)
{
	int	cx;
	int	cy;
	int	dx;

	if (!cube->inp.mouse_captured)
		return ;
	mlx_mouse_get_pos(cube->render.mlx, cube->render.win, &cx, &cy);
	if (cx == SCR_W / 2)
		return ;
	dx = cx - (SCR_W / 2);
	cube->inp.mouse_angle += dx * cube->inp.sens;
	mlx_mouse_move(cube->render.mlx, cube->render.win, SCR_W / 2, SCR_H / 2);
}

void	mouse_capture_set(t_game *cube, int enable)
{
	cube->inp.mouse_captured = (enable != 0);
	if (cube->inp.mouse_captured)
	{
		mlx_mouse_hide(cube->render.mlx, cube->render.win);
		cube->inp.last_x = SCR_W / 2;
		cube->inp.last_y = SCR_H / 2;
	}
	else
		mlx_mouse_show(cube->render.mlx, cube->render.win);
}

int	mouse_move(int x, int y, void *param)
{
	t_game	*cube;
	int		cx;
	int		cy;
	int		dx;
	int		dy;

	cube = (t_game *)param;
	if (!cube || !cube->inp.mouse_captured)
		return (0);
	cx = SCR_W / 2;
	cy = SCR_H / 2;
	dx = x - cx;
	dy = y - cy;
	if (dx != 0)
		cube->inp.mouse_angle += (double)dx * cube->inp.sens;
	if (dy != 0)
		cube->inp.mouse_dy += (double)dy;
	mlx_mouse_move(cube->render.mlx, cube->render.win, cx, cy);
	return (0);
}
