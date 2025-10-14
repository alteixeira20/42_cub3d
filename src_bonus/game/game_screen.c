/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:33:13 by jopedro-          #+#    #+#             */
/*   Updated: 2025/10/13 13:58:55 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cub3d_bonus.h"

void game_over(t_game *cube)
{
	mlx_clear_window(cube->render.mlx, cube->render.win);
	mlx_put_image_to_window(cube->render.mlx, cube->render.win, END_IMAGE, 0, 0);
}
