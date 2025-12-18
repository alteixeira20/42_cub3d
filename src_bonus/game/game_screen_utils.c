/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screen_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:40:00 by paalexan          #+#    #+#             */
/*   Updated: 2025/12/18 16:30:45 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	overlay_dim_frame(t_game *cube)
{
	int				x;
	int				y;
	int				step;
	t_img			*frame;
	unsigned char	*px;

	frame = &cube->render.frame;
	if (!frame->addr || frame->w <= 0 || frame->h <= 0)
		return ;
	step = frame->bpp / 8;
	if (step < 3)
		return ;
	overlay_frame_helper(frame, px, step);
}

void	overlay_fill_color(t_img *img, unsigned int color)
{
	int				x;
	int				y;
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

static void	overlay_blit_row(t_blit_ctx *ctx, int y)
{
	int				x;
	int				dx;
	int				dy;
	unsigned int	color;

	dy = ctx->start_y + y;
	if (dy < 0 || dy >= SCR_H)
		return ;
	x = 0;
	while (x < ctx->img->w)
	{
		dx = ctx->start_x + x;
		if (dx >= 0 && dx < SCR_W)
		{
			color = get_texel(ctx->img, x, y);
			if (color != ctx->trans)
				put_pixel_img(&ctx->cube->render.frame, dx, dy, color);
		}
		x++;
	}
}

void	overlay_blit_centered(t_game *cube, t_img *img)
{
	t_blit_ctx	ctx;
	int			y;

	if (!img || !img->img || !img->addr)
		return ;
	ctx.cube = cube;
	ctx.img = img;
	ctx.trans = get_texel(img, 0, 0);
	ctx.start_x = (SCR_W - img->w) / 2;
	ctx.start_y = (SCR_H - img->h) / 2;
	y = 0;
	while (y < img->h)
	{
		overlay_blit_row(&ctx, y);
		y++;
	}
}
