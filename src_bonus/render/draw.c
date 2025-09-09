/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:34:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 11:58:58 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static inline unsigned int	get_texel(const t_img *img, int x, int y)
{
	char			*px;
	unsigned int	color;

	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	color = *(unsigned int *)px;
	return (color);
}

static inline void	img_put_pixel(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}

static void	draw_helper(t_game *cube, t_ray *r, int x)
{
	t_img			*tex;
	unsigned int	color;
	int				y;
	int				tex_y;

	tex = &cube->tex_rt[r->tex_id].img;
	y = 0;
	while (y < r->draw_start)
		img_put_pixel(&cube->render.frame, x, y++, cube->ceil_color.argb);
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->h)
			tex_y = tex->h - 1;
		color = get_texel(tex, r->tex_x, tex_y);
		if (r->side == 1)
			color = ((color & 0xFFFEFEFE) >> 1);
		img_put_pixel(&cube->render.frame, x, y, color);
		r->tex_pos += r->step;
		y++;
	}
}

static void	draw_column(t_game *cube, int x, t_ray *r)
{
	int				y;

	draw_helper(cube, r, x);
	y = r->draw_end + 1;
	if (y < 0)
	{
		y = 0;
	}
	while (y < SCR_H)
	{
		img_put_pixel(&cube->render.frame, x, y, cube->floor_color.argb);
		y++;
	}
}

void	draw_frame(t_game *cube)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < SCR_W)
	{
		ray_setup(cube, &r, x);
		ray_dda(cube, &r);
		r.tex_id = ray_pick_tex(&r);
		ray_compute_lines(cube, &r);
		ray_texcoords_setup(cube, &r);
		draw_column(cube, x, &r);
		x++;
	}
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
	draw_crosshair(cube);
	render_minimap(cube);
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->minimap.img_ptr,
		cube->minimap.offset_x,
		cube->minimap.offset_y);
}
