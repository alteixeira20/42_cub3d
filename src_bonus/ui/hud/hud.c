/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:20:46 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 19:04:12 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

void	hud_init(t_hud_ctx *ctx, t_img *frame)
{
	if (!ctx || !frame)
		return ;
	ctx->img = frame;
	ctx->scale = KEY_TEXT_SCALE;
	ctx->color = 0xFFFFFF;
	ctx->x = 20;
	ctx->y = 20;
	ctx->text = NULL;
}

void	hud_draw_collected(t_game *cube)
{
	char		*msg;
	t_hud_ctx	ctx;

	if (!cube || cube->collect.count <= 0)
		return ;
	msg = hud_make_counter_text(cube);
	if (!msg)
		return ;
	hud_init(&ctx, &cube->render.frame);
	ctx.text = msg;
	hud_put_text(cube, &ctx);
	free(msg);
}
