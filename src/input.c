/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:13:40 by jopedro-          #+#    #+#             */
/*   Updated: 2025/08/13 16:14:37 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 18:25:00 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/13 18:25:00 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int keycode, t_game *cube)
{
	if (keycode == KEY_W)
		cube->inp.forward = 1;
	else if (keycode == KEY_S)
		cube->inp.backward = 1;
	else if (keycode == KEY_A)
		cube->inp.left = 1;
	else if (keycode == KEY_D)
		cube->inp.right = 1;
	else if (keycode == KEY_LEFT)
		cube->inp.turn_l = 1;
	else if (keycode == KEY_RIGHT)
		cube->inp.turn_r = 1;
	else if (keycode == KEY_ESC)
		return (win_close(cube), 0);
	return (0);
}

int	key_release(int keycode, t_game *cube)
{
	if (keycode == KEY_W)
		cube->inp.forward = 0;
	else if (keycode == KEY_S)
		cube->inp.backward = 0;
	else if (keycode == KEY_A)
		cube->inp.left = 0;
	else if (keycode == KEY_D)
		cube->inp.right = 0;
	else if (keycode == KEY_LEFT)
		cube->inp.turn_l = 0;
	else if (keycode == KEY_RIGHT)
		cube->inp.turn_r = 0;
	return (0);
}
