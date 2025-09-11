/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:49:36 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/10 16:52:05 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	advance_one_step(t_game *c, t_ray *r)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	if (r->map_x < 0 || r->map_y < 0
		|| r->map_x >= c->map.width || r->map_y >= c->map.height)
		return (1);
	return (0);
}

int	ray_find_wall_behind_door(t_game *c, t_ray *rb)
{
	int	done;

	done = 0;
	while (!done)
	{
		if (advance_one_step(c, rb))
			return (0);
		if (c->map.grid[rb->map_y][rb->map_x] == '1')
		{
			rb->hit_type = 1;
			return (1);
		}
		if (c->map.grid[rb->map_y][rb->map_x] == 'D')
		{
			if (door_blocks_cell(&c->doors, rb->map_x, rb->map_y))
				return (0);
		}
	}
	return (0);
}

void	draw_slice(t_game *c, t_ray *r, int x)
{
	t_img			*tex;
	unsigned int	color;
	int				y;
	int				tex_y;

	tex = &c->tex_rt[r->tex_id].img;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)r->tex_pos;
		if (r->tex_id == TEX_DO)
			tex_y -= r->tex_y_off;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->h)
			tex_y = tex->h - 1;
		color = get_texel(tex, r->tex_x, tex_y);
		if (r->side == 1)
			color = ((color & 0xFFFEFEFE) >> 1);
		img_put_pixel(&c->render.frame, x, y, color);
		r->tex_pos += r->step;
		y++;
	}
}
