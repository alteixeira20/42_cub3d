/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:16:47 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 17:16:57 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

unsigned int	get_texel(const t_img *img, int x, int y)
{
	char			*px;
	unsigned int	color;

	px = NULL;
	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	color = *(unsigned int *)px;
	return (color);
}

void	put_pixel_img(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	px = NULL;
	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}
