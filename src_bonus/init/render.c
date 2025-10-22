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

void	render_init(t_game *cube)
{
	t_render	*render;

	render = &cube->render;
	render->mlx = NULL;
	render->win = NULL;
	render->frame.img = NULL;
	render->frame.addr = NULL;
	render->frame.bpp = 0;
	render->frame.line_len = 0;
	render->frame.endian = 0;
	render->frame.w = 0;
	render->frame.h = 0;
	render->end_screen.img = NULL;
	render->end_screen.addr = NULL;
	render->end_screen.bpp = 0;
	render->end_screen.line_len = 0;
	render->end_screen.endian = 0;
	render->end_screen.w = 0;
	render->end_screen.h = 0;
	render->pause_screen.img = NULL;
	render->pause_screen.addr = NULL;
	render->pause_screen.bpp = 0;
	render->pause_screen.line_len = 0;
	render->pause_screen.endian = 0;
	render->pause_screen.w = 0;
	render->pause_screen.h = 0;
	render->start_screen.img = NULL;
	render->start_screen.addr = NULL;
	render->start_screen.bpp = 0;
	render->start_screen.line_len = 0;
	render->start_screen.endian = 0;
	render->start_screen.w = 0;
	render->start_screen.h = 0;
}
