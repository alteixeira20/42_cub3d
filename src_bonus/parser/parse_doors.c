/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:07:30 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/09 21:32:11 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static size_t	count_doors(char **map)
{
	size_t	i;
	size_t	j;
	size_t	n;

	i = 0;
	n = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == DOOR_CELL)
				n++;
			j++;
		}
		i++;
	}
	return (n);
}

int	doors_build(char **map, t_doors *doors)
{
	size_t	i;
	size_t	j;
	size_t	k;

	doors->len = count_doors(map);
	if (doors->len == 0)
	{
		doors->arr = NULL;
		return (0);
	}
	doors->arr = (t_door *)malloc(sizeof(t_door) * doors->len);
	if (!doors->arr)
		return (-1);
	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == DOOR_CELL && k < doors->len)
			{
				doors->arr[k].grid_x = (int)j;
				doors->arr[k].grid_y = (int)i;
				doors->arr[k].open_t = 0.0f;
				doors->arr[k].opening = 0;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	parse_doors(t_game *cube)
{
	doors_build(cube->map.grid, &cube->doors);
}
