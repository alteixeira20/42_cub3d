/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:34:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 17:09:29 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	img_put_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}

void		draw_column(t_game *c, int x, t_ray *r)
{
	int		y;
	t_ray	rb;

	y = 0;
	while (y < r->draw_start)
		img_put_pixel(&c->render.frame, x, y++, c->ceil_color.argb);
	if (r->tex_id == TEX_DO)
	{
		rb = *r;
		if (ray_find_wall_behind_door(c, &rb))
		{
			rb.tex_id = ray_pick_tex(&rb);
			ray_compute_lines(c, &rb);
			ray_texcoords_setup(c, &rb);
			draw_slice(c, &rb, x);
		}
	}
	draw_slice(c, r, x);
	y = r->draw_end + 1;
	if (y < 0)
		y = 0;
	while (y < SCR_H)
	{
		img_put_pixel(&c->render.frame, x, y, c->floor_color.argb);
		y++;
	}
}

void	draw_frame(t_game *cube)
{
	int		x;
	t_ray	r;

	update_doors_for_frame(cube);
	x = 0;
	while (x < SCR_W)
	{
		ray_setup(cube, &r, x);
		ray_dda(cube, &r);
		r.tex_id = ray_pick_tex(&r);
		ray_compute_lines(cube, &r);
		apply_door_sink(cube, &r);
		cube->zbuf[x] = r.perp_dist;
		ray_texcoords_setup(cube, &r);
		draw_column(cube, x, &r);
		x++;
	}
	collectibles_draw(cube);
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
