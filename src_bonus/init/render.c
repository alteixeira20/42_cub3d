/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:26:41 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 19:28:58 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	img_reset(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->w = 0;
	img->h = 0;
}

void	render_init(t_game *cube)
{
	t_render	*render;

	render = &cube->render;
	render->mlx = NULL;
	render->win = NULL;
	img_reset(&render->frame);
	img_reset(&render->end_screen);
	img_reset(&render->pause_screen);
	img_reset(&render->start_screen);
}
