/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:52:01 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 18:14:20 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	ray_set_dir(t_game *cube, t_ray *r)
{
	if (r->ray_dir_x < 0.0)
	{
		r->step_x = -1;
		r->side_dist_x = (cube->player.pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - cube->player.pos_x) * r->delta_x;
	}
	if (r->ray_dir_y < 0.0)
	{
		r->step_y = -1;
		r->side_dist_y = (cube->player.pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - cube->player.pos_y) * r->delta_y;
	}
}

int	ray_pick_tex(const t_ray *r)
{
	if (r->hit_type == 2)
		return (TEX_DO);
	if (r->side == 0)
	{
		if (r->ray_dir_x < 0.0)
			return (TEX_WE);
		else
			return (TEX_EA);
	}
	if (r->ray_dir_y < 0.0)
		return (TEX_NO);
	return (TEX_SO);
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
	r->base_bottom = r->draw_end;
}
