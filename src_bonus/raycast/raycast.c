/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:36:06 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 18:18:53 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	step_in_x(t_ray *r)
{
	r->side_dist_x += r->delta_x;
	r->map_x += r->step_x;
	r->side = 0;
}

static void	step_in_y(t_ray *r)
{
	r->side_dist_y += r->delta_y;
	r->map_y += r->step_y;
	r->side = 1;
}

static int	check_hit(t_game *c, t_ray *r)
{
	char	cell;

	if (r->map_x < 0 || r->map_y < 0
		|| r->map_x >= c->map.width || r->map_y >= c->map.height)
		return (1);
	cell = c->map.grid[r->map_y][r->map_x];
	if (cell == '1')
	{
		r->hit_type = 1;
		return (1);
	}
	else if (cell == 'D')
	{
		if (!door_blocks_cell(&c->doors, r->map_x, r->map_y))
			return (0);
		r->hit_type = 2;
		return (1);
	}
	return (0);
}

void	ray_dda(t_game *c, t_ray *r)
{
	while (1)
	{
		if (r->side_dist_x < r->side_dist_y)
			step_in_x(r);
		else
			step_in_y(r);
		if (check_hit(c, r))
			break ;
	}
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
	if ((r->side == 0 && r->ray_dir_x < 0.0)
		|| (r->side == 1 && r->ray_dir_y > 0.0))
		r->tex_x = tex_w - r->tex_x - 1;
	r->step = (double)tex_h / (double)r->line_h;
	v_offset = (int)(-cube->player.pitch * SCR_H);
	r->tex_pos = ((r->draw_start - v_offset)
			- SCR_H / 2 + r->line_h / 2) * r->step;
}
