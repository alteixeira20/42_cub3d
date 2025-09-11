/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:15:18 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 18:15:10 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	tex_rt_init(t_game *cube)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		cube->tex_rt[i].img.img = NULL;
		cube->tex_rt[i].img.addr = NULL;
		cube->tex_rt[i].img.bpp = 0;
		cube->tex_rt[i].img.line_len = 0;
		cube->tex_rt[i].img.endian = 0;
		cube->tex_rt[i].img.w = 0;
		cube->tex_rt[i].img.h = 0;
		i++;
	}
}

void	raycast_init(t_game *cube, t_ray *r, int x)
{
	r->camera_x = 2.0 * x / (double)SCR_W - 1.0;
	r->ray_dir_x = cube->player.dir_x + cube->player.plane_x * r->camera_x;
	r->ray_dir_y = cube->player.dir_y + cube->player.plane_y * r->camera_x;
	r->map_x = (int)cube->player.pos_x;
	r->map_y = (int)cube->player.pos_y;
	r->hit_type = 0;
	r->tex_y_off = 0;
	r->base_bottom = 0;
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
