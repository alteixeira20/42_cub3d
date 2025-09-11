/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:34:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 14:44:57 by paalexan         ###   ########.fr       */
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

	if (r->tex_id == TEX_DO)
	{
		/* cache door overlay ray for later pass */
		c->door_hit[x] = 1;
		c->door_ray[x] = *r;
		/* Build baseline from the wall behind the door */
		rb = *r;
		if (ray_find_wall_behind_door(c, &rb))
		{
			rb.tex_id = ray_pick_tex(&rb);
			ray_compute_lines(c, &rb);
			ray_texcoords_setup(c, &rb);
			/* set z-buffer to background so sprites are culled by wall */
			c->zbuf[x] = rb.perp_dist;
			/* ceiling up to wall start */
			y = 0;
			while (y < rb.draw_start)
				img_put_pixel(&c->render.frame, x, y++, c->ceil_color.argb);
			/* wall behind door */
			draw_slice(c, &rb, x);
			/* floor after wall */
			y = rb.draw_end + 1;
			if (y < 0)
				y = 0;
			while (y < SCR_H)
			{
				img_put_pixel(&c->render.frame, x, y, c->floor_color.argb);
				y++;
			}
		}
		else
		{
			/* no wall found; set far so sprites can render */
			c->zbuf[x] = 1e9;
			/* No wall behind (should be rare); fill ceiling+floor normally */
			y = 0;
			while (y < r->draw_start)
				img_put_pixel(&c->render.frame, x, y++, c->ceil_color.argb);
			y = r->draw_end + 1;
			if (y < 0)
				y = 0;
			while (y < SCR_H)
			{
				img_put_pixel(&c->render.frame, x, y, c->floor_color.argb);
				y++;
			}
		}
		return ;
	}
	/* Normal wall column */
	c->zbuf[x] = r->perp_dist;
	y = 0;
	while (y < r->draw_start)
		img_put_pixel(&c->render.frame, x, y++, c->ceil_color.argb);
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
	/* reset door overlay cache */
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
	/* draw door overlays after sprites to occlude progressively */
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
