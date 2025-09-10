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

static void	dim_screen(t_game *cube)
{
	int		x;
	int		y;
	char	*px;

	y = 0;
	while (y < SCR_H)
	{
		x = 0;
		while (x < SCR_W)
		{
			px = cube->render.frame.addr;
			px += y * cube->render.frame.line_len;
			px += x * (cube->render.frame.bpp / 8);
			px[0] = px[0] / 2;
			px[1] = px[1] / 2;
			px[2] = px[2] / 2;
			x++;
		}
		y++;
	}
}

static void	draw_pause_overlay(t_game *cube)
{
	dim_screen(cube);
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
	mlx_string_put(cube->render.mlx, cube->render.win,
		SCR_W / 2 - 40, SCR_H / 2 - 20, 0xFFFFFF, "PAUSED");
	mlx_string_put(cube->render.mlx, cube->render.win,
		SCR_W / 2 - 80, SCR_H / 2 + 20, 0xAAAAAA, "Press M to start again");
}

int	game_loop(void *param)
{
	t_game	*cube;

	cube = (t_game *)param;
	if (!cube->paused)
	{
		update_player(cube);
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
