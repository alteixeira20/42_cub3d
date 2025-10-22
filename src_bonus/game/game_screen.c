/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:33:13 by jopedro-          #+#    #+#             */
/*   Updated: 2025/10/13 13:58:55 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cub3d_bonus.h"

void	overlay_dim_frame(t_game *cube)
{
	int		x;
	int		y;
	unsigned char	*px;
	t_img			*frame;
	int			step;

	frame = &cube->render.frame;
	if (!frame->addr || frame->w <= 0 || frame->h <= 0)
		return ;
	step = frame->bpp / 8;
	if (step < 3)
		return ;
	y = 0;
	while (y < frame->h)
	{
		x = 0;
		while (x < frame->w)
		{
			px = (unsigned char *)(frame->addr
				+ y * frame->line_len
				+ x * step);
			px[0] /= 2;
			px[1] /= 2;
			px[2] /= 2;
			x++;
		}
		y++;
	}
}

void	overlay_fill_color(t_img *img, unsigned int color)
{
	int		x;
	int		y;
	unsigned int	pixel;

	if (!img || !img->addr || img->w <= 0 || img->h <= 0)
		return ;
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			pixel = color;
			put_pixel_img(img, x, y, pixel);
			x++;
		}
		y++;
	}
}

int	overlay_load_image(t_game *cube, t_img *slot, const char *path)
{
	if (!slot)
		return (-1);
	if (slot->img)
		return (0);
	slot->img = mlx_xpm_file_to_image(cube->render.mlx,
		(char *)path, &slot->w, &slot->h);
	if (!slot->img)
		return (-1);
	slot->addr = mlx_get_data_addr(slot->img, &slot->bpp,
		&slot->line_len, &slot->endian);
	if (!slot->addr)
	{
		mlx_destroy_image(cube->render.mlx, slot->img);
		slot->img = NULL;
		slot->addr = NULL;
		slot->w = 0;
		slot->h = 0;
		slot->bpp = 0;
		slot->line_len = 0;
		slot->endian = 0;
		return (-1);
	}
	return (0);
}

void	overlay_blit_centered(t_game *cube, t_img *img)
{
	unsigned int	trans;
	unsigned int	color;
	int			start_x;
	int			start_y;
	int			dx;
	int			dy;
	int			x;
	int			y;

	if (!img || !img->img || !img->addr)
		return ;
	trans = get_texel(img, 0, 0);
	start_x = (SCR_W - img->w) / 2;
	start_y = (SCR_H - img->h) / 2;
	y = 0;
	while (y < img->h)
	{
		dy = start_y + y;
		if (dy >= 0 && dy < SCR_H)
		{
			x = 0;
			while (x < img->w)
			{
				dx = start_x + x;
				if (dx >= 0 && dx < SCR_W)
				{
					color = get_texel(img, x, y);
					if (color != trans)
						put_pixel_img(&cube->render.frame, dx, dy, color);
				}
				x++;
			}
		}
		y++;
	}
}

void	draw_game_over(t_game *cube)
{
	if (!cube || !cube->render.mlx || !cube->render.win)
		return ;
	if (!cube->end_dimmed)
	{
		draw_frame(cube);
		overlay_dim_frame(cube);
		if (overlay_load_image(cube, &cube->render.end_screen,
			END_SCREEN_PATH) == 0)
		{
			overlay_blit_centered(cube, &cube->render.end_screen);
			cube->end_overlay = true;
		}
		cube->end_dimmed = true;
	}
	else if (!cube->end_overlay
		&& overlay_load_image(cube, &cube->render.end_screen,
			END_SCREEN_PATH) == 0)
	{
		overlay_blit_centered(cube, &cube->render.end_screen);
		cube->end_overlay = true;
	}
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
}

void	game_over(t_game *cube)
{
	if (!cube || cube->ended)
		return ;
	cube->ended = true;
	cube->paused = false;
	cube->end_dimmed = false;
	cube->end_overlay = false;
	cube->pause_dimmed = false;
	cube->pause_overlay = false;
	cube->start_overlay = false;
	cube->started = true;
	mouse_capture_set(cube, 0);
	draw_game_over(cube);
}

void	draw_start_screen(t_game *cube)
{
	if (!cube || !cube->render.mlx || !cube->render.win)
		return ;
	if (!cube->start_overlay)
	{
		overlay_fill_color(&cube->render.frame, 0x000000);
		if (overlay_load_image(cube, &cube->render.start_screen,
			START_SCREEN_PATH) == 0)
			overlay_blit_centered(cube, &cube->render.start_screen);
		cube->start_overlay = true;
	}
	else if (cube->render.start_screen.img
		&& cube->render.start_screen.addr)
	{
		overlay_blit_centered(cube, &cube->render.start_screen);
	}
	mlx_put_image_to_window(cube->render.mlx, cube->render.win,
		cube->render.frame.img, 0, 0);
	mlx_string_put(cube->render.mlx, cube->render.win,
		SCR_W / 2 - 120, SCR_H / 2 + 120,
		0xFFFFFF, "Press ENTER to start");
}
