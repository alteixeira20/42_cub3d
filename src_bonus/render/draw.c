/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:34:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 18:15:32 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	img_put_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}

static void	clear_door_hits(t_game *c)
{
	int	x;

	x = 0;
	while (x < SCR_W)
	{
		c->door_hit[x] = 0;
		x++;
	}
}

static void	render_columns(t_game *c)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < SCR_W)
	{
		raycast_init(c, &r, x);
		ray_dda(c, &r);
		r.tex_id = ray_pick_tex(&r);
		ray_compute_lines(c, &r);
		apply_door_sink(c, &r);
		ray_texcoords_setup(c, &r);
		draw_column(c, x, &r);
		x++;
	}
}

static void	render_doors(t_game *c)
{
	int	x;

	x = 0;
	while (x < SCR_W)
	{
		if (c->door_hit[x])
			draw_slice(c, &c->door_ray[x], x);
		x++;
	}
}

void	draw_frame(t_game *c)
{
	update_doors_for_frame(c);
	clear_door_hits(c);
	render_columns(c);
	collectibles_draw(c);
	render_doors(c);
	hud_draw_collected(c);
	mlx_put_image_to_window(c->render.mlx, c->render.win,
		c->render.frame.img, 0, 0);
	draw_crosshair(c);
	render_minimap(c);
	mlx_put_image_to_window(c->render.mlx, c->render.win,
		c->minimap.img_ptr,
		c->minimap.offset_x,
		c->minimap.offset_y);
}
