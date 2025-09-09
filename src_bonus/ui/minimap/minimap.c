/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:05:57 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 15:09:26 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

static void	draw_mm_row(t_game *cube, int py)
{
	t_minimap		*m;
	int				px;
	double			denom;
	double			sy;
	unsigned int	color;

	m = &cube->minimap;
	denom = (double)m->tile_size * m->scale;
	sy = ((double)py - (m->height / 2.0)) / denom;
	px = 0;
	while (px < m->width)
	{
		color = sample2x2(cube, ((double)px - (m->width / 2.0)) / denom, sy);
		put_pixel(m, px, py, color);
		px++;
	}
}

static void	draw_minimap_pixels(t_game *cube)
{
	int			py;
	t_minimap	*m;

	m = &cube->minimap;
	py = 0;
	while (py < m->height)
	{
		draw_mm_row(cube, py);
		py++;
	}
}

void	render_minimap(t_game *cube)
{
	t_minimap	*m;

	m = &cube->minimap;
	if (!m->enabled)
		return ;
	clear_minimap(m, MM_COLOR_VOID);
	draw_minimap_pixels(cube);
	render_player_pos(cube);
	draw_border(m, MM_COLOR_BORDER);
}
