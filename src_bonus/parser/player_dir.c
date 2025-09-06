/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:11:47 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 16:24:19 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	set_dir_and_plane_no(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0;
}

static void	set_dir_and_plane_so(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0;
}

static void	set_dir_and_plane_ea(t_game *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

static void	set_dir_and_plane_we(t_game *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = -0.66;
}

void	set_dir_and_plane(t_game *game, char c)
{
	if (c == 'N')
		set_dir_and_plane_no(game);
	else if (c == 'S')
		set_dir_and_plane_so(game);
	else if (c == 'E')
		set_dir_and_plane_ea(game);
	else if (c == 'W')
		set_dir_and_plane_we(game);
}
