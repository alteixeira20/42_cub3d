/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alteixeira20 <paalexan@student.42porto.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:09:53 by alteixeira20      #+#    #+#             */
/*   Updated: 2025/12/18 16:12:59 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	render_destroy_frame(t_render *r)
{
	if (r->frame.img)
		mlx_destroy_image(r->mlx, r->frame.img);
	r->frame.img = NULL;
	r->frame.addr = NULL;
	r->frame.bpp = 0;
	r->frame.line_len = 0;
	r->frame.endian = 0;
	r->frame.w = 0;
	r->frame.h = 0;
}

void	render_destroy_end_screen(t_render *r)
{
	if (r->end_screen.img)
		mlx_destroy_image(r->mlx, r->end_screen.img);
	r->end_screen.img = NULL;
	r->end_screen.addr = NULL;
	r->end_screen.bpp = 0;
	r->end_screen.line_len = 0;
	r->end_screen.endian = 0;
	r->end_screen.w = 0;
	r->end_screen.h = 0;
}

void	render_destroy_pause_screen(t_render *r)
{
	if (r->pause_screen.img)
		mlx_destroy_image(r->mlx, r->pause_screen.img);
	r->pause_screen.img = NULL;
	r->pause_screen.addr = NULL;
	r->pause_screen.bpp = 0;
	r->pause_screen.line_len = 0;
	r->pause_screen.endian = 0;
	r->pause_screen.w = 0;
	r->pause_screen.h = 0;
}

void	render_destroy_start_screen(t_render *r)
{
	if (r->start_screen.img)
		mlx_destroy_image(r->mlx, r->start_screen.img);
	r->start_screen.img = NULL;
	r->start_screen.addr = NULL;
	r->start_screen.bpp = 0;
	r->start_screen.line_len = 0;
	r->start_screen.endian = 0;
	r->start_screen.w = 0;
	r->start_screen.h = 0;
}

void	render_destroy(t_game *cube)
{
	if (cube->render.mlx)
	{
		render_destroy_frame(&cube->render);
		render_destroy_end_screen(&cube->render);
		render_destroy_pause_screen(&cube->render);
		render_destroy_start_screen(&cube->render);
		if (cube->render.win)
			mlx_destroy_window(cube->render.mlx, cube->render.win);
		mlx_destroy_display(cube->render.mlx);
		free(cube->render.mlx);
	}
	cube->render.mlx = NULL;
	cube->render.win = NULL;
}
