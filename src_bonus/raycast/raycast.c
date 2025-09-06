/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:36:06 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/06 16:01:59 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	ray_setup(t_game *cube, t_ray *r, int x)
{
	r->camera_x = 2.0 * x / (double)SCR_W - 1.0;
	r->ray_dir_x = cube->player.dir_x + cube->player.plane_x * r->camera_x;
	r->ray_dir_y = cube->player.dir_y + cube->player.plane_y * r->camera_x;
	r->map_x = (int)cube->player.pos_x;
	r->map_y = (int)cube->player.pos_y;
	if (r->ray_dir_x == 0.0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0.0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->ray_dir_y);
	ray_set_dir(cube, r);
}

void	ray_dda(t_game *cube, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
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
			|| r->map_x >= cube->map.width || r->map_y >= cube->map.height)
			break ;
		if (cube->map.grid[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

void	ray_compute_lines(t_game *cube, t_ray *r)
{
	int	v_offset;

	if (r->side == 0)
		r->perp_dist = (r->map_x - cube->player.pos_x
				+ (1 - r->step_x) * 0.5) / r->ray_dir_x;
	else
		r->perp_dist = (r->map_y - cube->player.pos_y
				+ (1 - r->step_y) * 0.5) / r->ray_dir_y;
	if (r->perp_dist < 1e-6)
		r->perp_dist = 1e-6;
	r->line_h = (int)(SCR_H / r->perp_dist);
	v_offset = (int)(-cube->player.pitch * SCR_H);
	r->draw_start = -r->line_h / 2 + SCR_H / 2 + v_offset;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_h / 2 + SCR_H / 2 + v_offset;
	if (r->draw_end >= SCR_H)
		r->draw_end = SCR_H - 1;
}

int	ray_pick_tex(const t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0.0)
			return (TEX_WE);
		else
			return (TEX_EA);
	}
	if (r->ray_dir_y > 0.0)
		return (TEX_NO);
	return (TEX_SO);
}

void	ray_texcoords_setup(t_game *cube, t_ray *r)
{
	t_img	*img;
	int		tex_w;
	int		tex_h;
	int		v_offset;

	img = &cube->tex_rt[r->tex_id].img;
	tex_w = img->w;
	tex_h = img->h;
	if (r->side == 0)
		r->wall_x = cube->player.pos_y + r->perp_dist * r->ray_dir_y;
	else
		r->wall_x = cube->player.pos_x + r->perp_dist * r->ray_dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)tex_w);
	if ((r->side == 0 && r->ray_dir_x > 0.0)
		|| (r->side == 1 && r->ray_dir_y < 0.0))
		r->tex_x = tex_w - r->tex_x - 1;
	r->step = (double)tex_h / (double)r->line_h;
	v_offset = (int)(-cube->player.pitch * SCR_H);
	r->tex_pos = ((r->draw_start - v_offset)
			- SCR_H / 2 + r->line_h / 2) * r->step;
}
