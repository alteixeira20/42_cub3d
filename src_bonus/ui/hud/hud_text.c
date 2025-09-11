/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:20:26 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 18:59:34 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

static const t_hud_glyph	*glyph_table(int idx)
{
	static const t_hud_glyph	g[] = {
	{'C', {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E}},
	{'o', {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E}},
	{'l', {0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06}},
	{'e', {0x00, 0x0E, 0x11, 0x1F, 0x10, 0x11, 0x0F}},
	{'c', {0x00, 0x00, 0x0E, 0x10, 0x10, 0x11, 0x0E}},
	{'t', {0x04, 0x04, 0x1F, 0x04, 0x04, 0x04, 0x03}},
	{'d', {0x01, 0x01, 0x0F, 0x11, 0x11, 0x11, 0x0F}},
	{' ', {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{'/', {0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10}},
	{'0', {0x0E, 0x13, 0x15, 0x19, 0x11, 0x11, 0x0E}},
	{'1', {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x0E}},
	{'2', {0x0E, 0x11, 0x01, 0x06, 0x08, 0x10, 0x1F}},
	{'3', {0x1F, 0x02, 0x04, 0x06, 0x01, 0x11, 0x0E}},
	{'4', {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02}},
	{'5', {0x1F, 0x10, 0x1E, 0x01, 0x01, 0x11, 0x0E}},
	{'6', {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E}},
	{'7', {0x1F, 0x01, 0x02, 0x04, 0x08, 0x08, 0x08}},
	{'8', {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E}},
	{'9', {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C}},
	};

	if (idx < 0 || idx >= (int)(sizeof(g) / sizeof(g[0])))
		return (NULL);
	return (&g[idx]);
}

static const t_hud_glyph	*get_glyph(char ch)
{
	int					i;
	const t_hud_glyph	*g;

	i = 0;
	g = glyph_table(i);
	if (g->c == ch)
		return (g);
	while (g)
	{
		g = glyph_table(i);
		if (g->c == ch)
			return (g);
		i++;
	}
	return (NULL);
}

static void	draw_block(const t_hud_ctx *ctx, int x, int y)
{
	int	sx;
	int	sy;

	sy = 0;
	while (sy < ctx->scale)
	{
		if (y + sy < 0 || y + sy >= ctx->img->h)
		{
			sy++;
			continue ;
		}
		sx = 0;
		while (sx < ctx->scale)
		{
			if (x + sx >= 0 && x + sx < ctx->img->w)
				put_pixel_img(ctx->img, x + sx, y + sy, ctx->color);
			sx++;
		}
		sy++;
	}
}

static void	draw_glyph(const t_hud_ctx *ctx, const t_hud_glyph *g)
{
	int				ry;
	int				rx;
	unsigned char	row;

	if (!g)
		return ;
	ry = 0;
	while (ry < 7)
	{
		row = g->rows[ry];
		rx = 0;
		while (rx < 5)
		{
			if (row & (1 << (4 - rx)))
				draw_block(ctx,
					ctx->x + rx * ctx->scale,
					ctx->y + ry * ctx->scale);
			rx++;
		}
		ry++;
	}
}

void	hud_put_text(t_game *cube, t_hud_ctx *ctx)
{
	const t_hud_glyph	*g;

	if (!cube || !ctx || !ctx->text)
		return ;
	while (*ctx->text)
	{
		g = get_glyph(*ctx->text);
		if (g)
			draw_glyph(ctx, g);
		ctx->x += 6 * ctx->scale;
		ctx->text++;
	}
}
