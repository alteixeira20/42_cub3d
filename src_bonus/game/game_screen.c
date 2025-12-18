/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:33:13 by jopedro-          #+#    #+#             */
/*   Updated: 2025/10/13 13:58:55 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	draw_end_overlay(t_game *cube)
{
	if (overlay_load_image(cube, &cube->render.end_screen,
			END_SCREEN_PATH) == 0)
	{
		overlay_blit_centered(cube, &cube->render.end_screen);
		cube->end_overlay = true;
	}
}

void	draw_game_over(t_game *cube)
{
	if (!cube || !cube->render.mlx || !cube->render.win)
		return ;
	if (!cube->end_dimmed)
	{
		draw_frame(cube);
		overlay_dim_frame(cube);
		draw_end_overlay(cube);
		cube->end_dimmed = true;
	}
	else if (!cube->end_overlay)
		draw_end_overlay(cube);
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
}

void	game_over(t_game *cube)
{
	if (!cube || cube->ended)
		return ;
	cube->ended = true;
	cube->paused = false;
	cube->end_dimmed = false;
	cube->end_overlay = false;
	cube->pause_dimmed = false;
	cube->pause_overlay = false;
	cube->start_overlay = false;
	cube->started = true;
	mouse_capture_set(cube, 0);
	draw_game_over(cube);
}

static void	draw_start_overlay(t_game *cube)
{
	overlay_fill_color(&cube->render.frame, 0x000000);
	if (overlay_load_image(cube, &cube->render.start_screen,
			START_SCREEN_PATH) == 0)
		overlay_blit_centered(cube, &cube->render.start_screen);
	cube->start_overlay = true;
}

void	draw_start_screen(t_game *cube)
{
	if (!cube || !cube->render.mlx || !cube->render.win)
		return ;
	if (!cube->start_overlay)
		draw_start_overlay(cube);
	else if (cube->render.start_screen.img
		&& cube->render.start_screen.addr)
	{
		overlay_blit_centered(cube, &cube->render.start_screen);
	}
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
	mlx_string_put(cube->render.mlx, cube->render.win,
		SCR_W / 2 - 120, SCR_H / 2 + 120,
		0xFFFFFF, "Press ENTER to start");
}
