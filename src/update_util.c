/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:11:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/03 18:25:32 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rotate_left(t_game *cube, double old_dir_x,
					double old_plane_x, double rs)
{
	cube->player.dir_x = cube->player.dir_x * cos(-rs)
		- cube->player.dir_y * sin(-rs);
	cube->player.dir_y = old_dir_x * sin(-rs)
		+ cube->player.dir_y * cos(-rs);
	cube->player.plane_x = cube->player.plane_x * cos(-rs)
		- cube->player.plane_y * sin(-rs);
	cube->player.plane_y = old_plane_x * sin(-rs)
		+ cube->player.plane_y * cos(-rs);
}

void	rotate_right(t_game *cube,
					double old_dir_x, double old_plane_x, double rs)
{
	cube->player.dir_x = cube->player.dir_x * cos(rs)
		- cube->player.dir_y * sin(rs);
	cube->player.dir_y = old_dir_x * sin(rs)
		+ cube->player.dir_y * cos(rs);
	cube->player.plane_x = cube->player.plane_x * cos(rs)
		- cube->player.plane_y * sin(rs);
	cube->player.plane_y = old_plane_x * sin(rs)
		+ cube->player.plane_y * cos(rs);
}
