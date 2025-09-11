/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:07:30 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/11 18:08:59 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static size_t	count_doors(const t_map *m)
{
	size_t			i;
	size_t			j;
	size_t			n;

	i = 0;
	n = 0;
	while (i < (size_t)m->height)
	{
		j = 0;
		while (m->grid[i][j])
		{
			if (m->grid[i][j] == DOOR_CELL)
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

static void	init_door(t_door *d, int x, int y)
{
	d->grid_x = x;
	d->grid_y = y;
	d->open_t = 0.0f;
	d->opening = 0;
}

static void	fill_doors(const t_map *m, t_doors *doors)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (i < (size_t)m->height)
	{
		j = 0;
		while (m->grid[i][j])
		{
			if (m->grid[i][j] == DOOR_CELL && k < doors->len)
				init_door(&doors->arr[k++], (int)j, (int)i);
			j++;
		}
		i++;
	}
}

static int	doors_build(const t_map *m, t_doors *doors)
{
	doors->len = count_doors(m);
	if (doors->len == 0)
	{
		doors->arr = NULL;
		return (0);
	}
	doors->arr = (t_door *)malloc(sizeof(t_door) * doors->len);
	if (!doors->arr)
		return (-1);
	fill_doors(m, doors);
	return (0);
}

void	parse_doors(t_game *cube)
{
	doors_build(&cube->map, &cube->doors);
}
