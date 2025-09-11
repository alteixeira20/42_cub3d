/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:15:18 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 17:19:43 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	tex_rt_init(t_game *cube)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		cube->tex_rt[i].img.img = NULL;
		cube->tex_rt[i].img.addr = NULL;
		cube->tex_rt[i].img.bpp = 0;
		cube->tex_rt[i].img.line_len = 0;
		cube->tex_rt[i].img.endian = 0;
		cube->tex_rt[i].img.w = 0;
		cube->tex_rt[i].img.h = 0;
		i++;
	}
}
