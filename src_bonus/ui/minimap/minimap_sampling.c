/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_sampling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:30:00 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 17:56:23 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

static void	avg_rgb_sum(unsigned int color, unsigned int *ra,
						unsigned int *ga, unsigned int *ba)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	get_rgb(color, &r, &g, &b);
	*ra += r;
	*ga += g;
	*ba += b;
}

static unsigned int	avg4(unsigned int a, unsigned int b,
						unsigned int c, unsigned int d)
{
	unsigned int	ra;
	unsigned int	ga;
	unsigned int	ba;

	ra = 0;
	ga = 0;
	ba = 0;
	avg_rgb_sum(a, &ra, &ga, &ba);
	avg_rgb_sum(b, &ra, &ga, &ba);
	avg_rgb_sum(c, &ra, &ga, &ba);
	avg_rgb_sum(d, &ra, &ga, &ba);
	ra = ra / 4;
	ga = ga / 4;
	ba = ba / 4;
	if (ra > 255)
		ra = 255;
	if (ga > 255)
		ga = 255;
	if (ba > 255)
		ba = 255;
	return (rgb(ra, ga, ba));
}

static unsigned int	sample_world(const t_game *cube, double wx, double wy)
{
	int	tx;
	int	ty;

	if (wx < 0.0 || wy < 0.0)
		return (0x00000000);
	tx = (int)wx;
	ty = (int)wy;
	if (tx < 0 || ty < 0 || ty >= cube->map.height || tx >= cube->map.width)
		return (0x00000000);
	return (tile_color(cube->map.grid[ty][tx]));
}

static unsigned int	sample_corner(const t_game *cube, double sx, double sy,
									int corner)
{
	double	o;
	double	ox;
	double	oy;
	double	dx;
	double	dy;

	if (cube->minimap.scale != 0.0)
		o = MM_SS_OFFSET / cube->minimap.scale;
	else
		o = MM_SS_OFFSET;
	if (corner % 2 == 0)
		ox = -o;
	else
		ox = o;
	if (corner / 2 == 0)
		oy = -o;
	else
		oy = o;
	dx = (sx + ox) * cube->player.plane_x - (sy + oy) * cube->player.dir_x;
	dy = (sx + ox) * cube->player.plane_y - (sy + oy) * cube->player.dir_y;
	return (sample_world(cube, cube->player.pos_x + dx,
			cube->player.pos_y + dy));
}

unsigned int	sample2x2(const t_game *cube, double sx, double sy)
{
	unsigned int	s[4];

	s[0] = sample_corner(cube, sx, sy, 0);
	s[1] = sample_corner(cube, sx, sy, 1);
	s[2] = sample_corner(cube, sx, sy, 2);
	s[3] = sample_corner(cube, sx, sy, 3);
	return (avg4(s[0], s[1], s[2], s[3]));
}
