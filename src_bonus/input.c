/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:13:40 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/05 16:17:45 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	key_press(int keycode, t_game *cube)
{
	if (keycode == KEY_W)
		cube->inp.forward = 1;
	if (keycode == KEY_S)
		cube->inp.backward = 1;
	if (keycode == KEY_A)
		cube->inp.left = 1;
	if (keycode == KEY_D)
		cube->inp.right = 1;
	if (keycode == KEY_ESC)
		return (win_close(cube), 0);
	return (0);
}

int	key_release(int keycode, t_game *cube)
{
	if (keycode == KEY_W)
		cube->inp.forward = 0;
	if (keycode == KEY_S)
		cube->inp.backward = 0;
	if (keycode == KEY_A)
		cube->inp.left = 0;
	if (keycode == KEY_D)
		cube->inp.right = 0;
	return (0);
}

#include <stdio.h>

int	mouse_move(int x, int y, t_game *cube)
{
	static int	init;
	static int	last_x;
	int			dx;
	double		sens;
	int			cx;

	(void)y;
	if (!init)
	{
		init = 1;
		last_x = x;
		return (0);
	}
	cx = SCR_W / 2;
	dx = x - last_x;
	if (dx != 0)
	{
		sens = 0.0000090;
		cube->inp.mouse_angle = cube->inp.mouse_angle + (double)dx * sens;
	}
	last_x = cx;
	mlx_mouse_move(cube->render.mlx, cube->render.win, SCR_W / 2, SCR_H / 2);
	return (0);
}
