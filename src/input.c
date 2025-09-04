/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:13:40 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/03 22:52:42 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	print_input_state(t_game *cube, const char *action, int key)
{
	ft_printf("[%s] Key: %d | W:%d A:%d S:%d D:%d L:%d R:%d\n",
		action, key,
		cube->inp.forward,
		cube->inp.left,
		cube->inp.backward,
		cube->inp.right,
		cube->inp.turn_l,
		cube->inp.turn_r);
}

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
	if (keycode == KEY_LEFT)
		cube->inp.turn_l = 1;
	if (keycode == KEY_RIGHT)
		cube->inp.turn_r = 1;
	if (keycode == KEY_ESC)
		return (win_close(cube), 0);
	print_input_state(cube, "PRESS", keycode);
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
	if (keycode == KEY_LEFT)
		cube->inp.turn_l = 0;
	if (keycode == KEY_RIGHT)
		cube->inp.turn_r = 0;
	print_input_state(cube, "RELEASE", keycode);
	return (0);
}
