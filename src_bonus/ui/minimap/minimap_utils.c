/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:31:21 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 15:09:02 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

void	put_pixel(t_minimap *m, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x < 0 || y < 0 || x >= m->width || y >= m->height)
		return ;
	offset = y * m->line_len + x * (m->bpp / 8);
	dst = m->addr + offset;
	*(unsigned int *)dst = color;
}

void	clear_minimap(t_minimap *m, int color)
{
	int		x;
	int		y;
	int		pxw;
	char	*dst;

	pxw = (m->bpp / 8);
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			dst = m->addr + y * m->line_len + x * pxw;
			*(unsigned int *)dst = (unsigned int)color;
			x++;
		}
		y++;
	}
}

void	draw_border(t_minimap *m, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->height)
	{
		put_pixel(m, 0, y, color);
		put_pixel(m, m->width - 1, y, color);
		y++;
	}
	x = 0;
	while (x < m->width)
	{
		put_pixel(m, x, 0, color);
		put_pixel(m, x, m->height - 1, color);
		x++;
	}
}

unsigned int	tile_color(char t)
{
	if (t == '1')
		return (MM_COLOR_WALL);
	if (t == '0')
		return (MM_COLOR_FLOOR);
	return (MM_COLOR_VOID);
}

void	render_player_pos(t_game *cube)
{
	int	x;
	int	y;
	int	cx;
	int	cy;
	int	r;

	cx = cube->minimap.width / 2;
	cy = cube->minimap.height / 2;
	r = 5;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				put_pixel(&cube->minimap, cx + x, cy + y, MM_COLOR_PLAYER);
			x++;
		}
		y++;
	}
}
