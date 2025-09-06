/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI_crosshair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:57:59 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 20:58:36 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	draw_crosshair(t_game *cube)
{
	int	cx;
	int	cy;
	int	size;

	cx = SCR_W / 2;
	cy = SCR_H / 2;
	size = 2;
	mlx_pixel_put(cube->render.mlx, cube->render.win, cx - size, cy, 0xFFFFFF);
	mlx_pixel_put(cube->render.mlx, cube->render.win, cx + size, cy, 0xFFFFFF);
	mlx_pixel_put(cube->render.mlx, cube->render.win, cx, cy - size, 0xFFFFFF);
	mlx_pixel_put(cube->render.mlx, cube->render.win, cx, cy + size, 0xFFFFFF);
}
