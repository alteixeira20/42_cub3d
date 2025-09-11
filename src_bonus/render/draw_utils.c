/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:52:39 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 17:58:42 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	draw_ceiling(t_game *c, int x, int limit)
{
	int	y;

	y = 0;
	while (y < limit)
		img_put_pixel(&c->render.frame, x, y++, c->ceil_color.argb);
}

static void	draw_floor(t_game *c, int x, int start)
{
	int	y;

	y = start;
	if (y < 0)
		y = 0;
	if (start < 0)
		start = 0;
	while (y < SCR_H)
	{
		img_put_pixel(&c->render.frame, x, y, c->floor_color.argb);
		y++;
	}
}

static void	draw_door_with_wall(t_game *c, int x, t_ray *rb)
{
	int	y;

	c->zbuf[x] = rb->perp_dist;
	draw_ceiling(c, x, rb->draw_start);
	draw_slice(c, rb, x);
	y = rb->draw_end + 1;
	draw_floor(c, x, y);
}

static void	draw_door_no_wall(t_game *c, int x, t_ray *r)
{
	int	y;

	c->zbuf[x] = 1e9;
	draw_ceiling(c, x, r->draw_start);
	y = r->draw_end + 1;
	draw_floor(c, x, y);
}

void	draw_column(t_game *c, int x, t_ray *r)
{
	t_ray	rb;

	if (r->tex_id == TEX_DO)
	{
		c->door_hit[x] = 1;
		c->door_ray[x] = *r;
		rb = *r;
		if (ray_find_wall_behind_door(c, &rb))
		{
			rb.tex_id = ray_pick_tex(&rb);
			ray_compute_lines(c, &rb);
			ray_texcoords_setup(c, &rb);
			draw_door_with_wall(c, x, &rb);
		}
		else
			draw_door_no_wall(c, x, r);
		return ;
	}
	c->zbuf[x] = r->perp_dist;
	draw_ceiling(c, x, r->draw_start);
	draw_slice(c, r, x);
	draw_floor(c, x, r->draw_end + 1);
}
