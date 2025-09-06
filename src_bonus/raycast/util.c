/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:52:01 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/03 18:54:19 by paalexan         ###   ########.fr       */
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
