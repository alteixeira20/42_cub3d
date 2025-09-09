/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:10:00 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 15:11:24 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

void	get_rgb(unsigned int c, unsigned int *r,
			unsigned int *g, unsigned int *b)
{
	*r = (c / 65536) % 256;
	*g = (c / 256) % 256;
	*b = c % 256;
}

unsigned int	rgb(unsigned int r, unsigned int g, unsigned int b)
{
	return (r * 65536 + g * 256 + b);
}
