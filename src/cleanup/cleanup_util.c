/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:50:55 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 15:54:45 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	clean_texture(t_texture *t)
{
	if (t->path)
	{
		free(t->path);
		t->path = NULL;
	}
	t->is_set = false;
}

void	clean_map(t_map *m)
{
	int	y;

	if (!m->grid)
		return ;
	y = 0;
	while (y < m->height)
	{
		free(m->grid[y]);
		y++;
	}
	free(m->grid);
	m->grid = NULL;
	m->width = 0;
	m->height = 0;
}
