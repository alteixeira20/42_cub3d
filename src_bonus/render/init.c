/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:50:59 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/10 19:34:24 by paalexan         ###   ########.fr       */
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

static void	render_destroy_frame(t_render *r)
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

static void	render_destroy_end_screen(t_render *r)
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

static void	render_destroy_pause_screen(t_render *r)
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

static void	render_destroy_start_screen(t_render *r)
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
