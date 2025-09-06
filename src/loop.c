/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:51 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/03 17:55:19 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	game_loop(void *param)
{
	t_game	*cube;

	cube = (t_game *)param;
	update_player(cube);
	draw_frame(cube);
	return (0);
}

int	win_close(t_game *cube)
{
	clean_game(cube);
	exit(0);
	return (0);
}
