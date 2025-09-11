/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_update_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:03:37 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/11 17:36:18 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

int	is_door_hit(const t_ray *r)
{
	return (r->hit_type == 2);
}

int	get_door_screen_offset(t_game *c, const t_ray *r)
{
	float	t;

	t = door_plane_offset(&c->doors, r->map_x, r->map_y);
	if (t < 0.0f)
		t = 0.0f;
	if (t > 1.0f)
		t = 1.0f;
	return ((int)(t * (float)r->line_h));
}

void	apply_door_sink(t_game *c, t_ray *r)
{
	int	off;
	int	vis_h;

	(void)c;
	if (!is_door_hit(r))
		return ;
	off = get_door_screen_offset(c, r);
	r->draw_start += off;
	r->draw_end += off;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end > r->base_bottom)
		r->draw_end = r->base_bottom;
	if (r->draw_end >= SCR_H)
		r->draw_end = SCR_H - 1;
	vis_h = r->draw_end - r->draw_start + 1;
	if (vis_h <= 0)
		return ;
	r->tex_y_off = (int)((float)off
			* ((float)c->tex_rt[TEX_DO].img.h / (float)r->line_h));
	if (r->tex_y_off < 0)
		r->tex_y_off = 0;
}
