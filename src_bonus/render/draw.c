/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:34:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 17:54:22 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	img_put_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}

void	draw_frame(t_game *cube)
{
	int		x;
	t_ray	r;

	update_doors_for_frame(cube);
	x = 0;
	while (x < SCR_W)
	{
		cube->door_hit[x] = 0;
		x++;
	}
	x = 0;
	while (x < SCR_W)
	{
		ray_setup(cube, &r, x);
		ray_dda(cube, &r);
		r.tex_id = ray_pick_tex(&r);
		ray_compute_lines(cube, &r);
		apply_door_sink(cube, &r);
		ray_texcoords_setup(cube, &r);
		draw_column(cube, x, &r);
		x++;
	}
	collectibles_draw(cube);
	x = 0;
	while (x < SCR_W)
	{
		if (cube->door_hit[x])
			draw_slice(cube, &cube->door_ray[x], x);
		x++;
	}
	hud_draw_collected(cube);
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
	draw_crosshair(cube);
	render_minimap(cube);
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->minimap.img_ptr,
		cube->minimap.offset_x,
		cube->minimap.offset_y);
}
