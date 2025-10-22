/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:13:40 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/06 15:16:17 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

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
	if (keycode == KEY_ENTER && !cube->started)
	{
		cube->started = true;
		cube->start_overlay = false;
		cube->pause_dimmed = false;
		cube->pause_overlay = false;
		mouse_capture_set(cube, 1);
		return (0);
	}
	if (keycode == KEY_P && cube->started && !cube->ended)
	{
		cube->paused = !cube->paused;
		cube->pause_dimmed = false;
		cube->pause_overlay = false;
		if (cube->paused)
			mouse_capture_set(cube, 0);
		else
			mouse_capture_set(cube, 1);
	}
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
