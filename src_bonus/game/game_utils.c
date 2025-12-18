/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alteixeira20 <paalexan@student.42porto.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 16:30:09 by alteixeira20      #+#    #+#             */
/*   Updated: 2025/12/18 16:30:31 by alteixeira20     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	overlay_frame_helper(t_img *frame, unsigned char *px, int step)
{
	int	x;
	int	y;

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
