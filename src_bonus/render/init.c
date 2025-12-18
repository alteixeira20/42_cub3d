/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:50:59 by jopedro-          #+#    #+#             */
/*   Updated: 2025/12/18 16:12:55 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	render_make_frame(t_render *r)
{
	r->frame.img = mlx_new_image(r->mlx, SCR_W, SCR_H);
	if (!r->frame.img)
		return (-1);
	r->frame.addr = mlx_get_data_addr(r->frame.img, &r->frame.bpp,
			&r->frame.line_len, &r->frame.endian);
	if (!r->frame.addr)
		return (-1);
	r->frame.w = SCR_W;
	r->frame.h = SCR_H;
	return (0);
}

int	render_init_win(t_game *cube)
{
	cube->render.mlx = mlx_init();
	if (!cube->render.mlx)
		return (-1);
	cube->render.win = mlx_new_window(cube->render.mlx, SCR_W, SCR_H, "cub3D");
	if (!cube->render.win)
	{
		mlx_destroy_display(cube->render.mlx);
		free(cube->render.mlx);
		return (-1);
	}
	if (render_make_frame(&cube->render) != 0)
	{
		mlx_destroy_window(cube->render.mlx, cube->render.win);
		mlx_destroy_display(cube->render.mlx);
		free(cube->render.mlx);
		return (-1);
	}
	return (0);
}
