/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:11:30 by paalexan          #+#    #+#             */
/*   Updated: 2025/10/13 13:58:28 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	update_anim(t_game *cube)
{
	static struct timeval	prev = {0, 0};
	struct timeval			now;
	double					dt;
	double					t;

	gettimeofday(&now, NULL);
	if (prev.tv_sec == 0 && prev.tv_usec == 0)
	{
		prev = now;
		return ;
	}
	dt = (now.tv_sec - prev.tv_sec)
		+ (now.tv_usec - prev.tv_usec) / 1000000.0;
	prev = now;
	t = cube->collect.anim_t + dt;
	if (t > 1000.0)
		t = 0.0;
	cube->collect.anim_t = t;
}

static void	try_collect(t_game *cube, t_collectible *c)
{
	double	dx;
	double	dy;
	double	d2;

	dx = c->pos_x - cube->player.pos_x;
	dy = c->pos_y - cube->player.pos_y;
	d2 = dx * dx + dy * dy;
	if (d2 <= (KEY_PICKUP_DIST * KEY_PICKUP_DIST))
	{
		c->collected = 1;
		cube->collect.collected = cube->collect.collected + 1;
		if (cube->collect.collected == cube->collect.count)
			game_over(cube);
	}
}

void	collectibles_update(t_game *cube)
{
	int	i;

	if (cube->ended)
		return ;
	update_anim(cube);
	if (cube->collect.count <= 0 || !cube->collect.items)
		return ;
	i = 0;
	while (i < cube->collect.count)
	{
		if (!cube->collect.items[i].collected)
			try_collect(cube, &cube->collect.items[i]);
		i = i + 1;
	}
}
