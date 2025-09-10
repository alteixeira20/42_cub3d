/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_query.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:09:48 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/09 16:10:21 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static const t_door	*find_door(const t_doors *doors, int gx, int gy)
{
	size_t	i;

	i = 0;
	while (i < doors->len)
	{
		if (doors->arr[i].grid_x == gx && doors->arr[i].grid_y == gy)
			return (&doors->arr[i]);
		i++;
	}
	return (NULL);
}

int	door_blocks_cell(const t_doors *doors, int gx, int gy)
{
	const t_door	*d;

	d = find_door(doors, gx, gy);
	if (!d)
		return (0);
	if (d->open_t >= 1.0f)
		return (0);
	return (1);
}

float	door_plane_offset(const t_doors *doors, int gx, int gy)
{
	const t_door	*d;

	d = find_door(doors, gx, gy);
	if (!d)
		return (0.0f);
	return (d->open_t * DOOR_THICK);
}
