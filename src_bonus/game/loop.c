/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:51 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/10 13:53:34 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	load_pause_screen(t_game *cube)
{
	return (overlay_load_image(cube, &cube->render.pause_screen,
		PAUSE_SCREEN_PATH));
}

static void	draw_pause_overlay(t_game *cube)
{
	if (!cube->pause_dimmed)
	{
		overlay_dim_frame(cube);
		if (load_pause_screen(cube) == 0)
		{
			overlay_blit_centered(cube, &cube->render.pause_screen);
			cube->pause_overlay = true;
		}
		cube->pause_dimmed = true;
	}
	else if (!cube->pause_overlay && load_pause_screen(cube) == 0)
	{
		overlay_blit_centered(cube, &cube->render.pause_screen);
		cube->pause_overlay = true;
	}
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
}

int	game_loop(void *param)
{
	t_game	*cube;

	cube = (t_game *)param;
	if (cube->ended)
	{
		draw_game_over(cube);
		return (0);
	}
	if (!cube->started)
	{
		draw_start_screen(cube);
		return (0);
	}
	if (!cube->paused)
	{
		cube->pause_dimmed = false;
		cube->pause_overlay = false;
		update_player(cube);
		if (cube->ended)
			draw_game_over(cube);
		else
			draw_frame(cube);
	}
	else
	{
		draw_pause_overlay(cube);
	}
	return (0);
}

int	win_close(t_game *cube)
{
	clean_game(cube);
	exit(0);
	return (0);
}
