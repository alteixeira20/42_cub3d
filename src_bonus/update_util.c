/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:11:36 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 17:59:58 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	rotate_player(t_game *cube, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cs;
	double	sn;

	old_dir_x = cube->player.dir_x;
	old_plane_x = cube->player.plane_x;
	cs = cos(angle);
	sn = sin(angle);
	cube->player.dir_x = cube->player.dir_x * cs - cube->player.dir_y * sn;
	cube->player.dir_y = old_dir_x * sn + cube->player.dir_y * cs;
	cube->player.plane_x = cube->player.plane_x * cs - cube->player.plane_y * sn;
	cube->player.plane_y = old_plane_x * sn + cube->player.plane_y * cs;
}

