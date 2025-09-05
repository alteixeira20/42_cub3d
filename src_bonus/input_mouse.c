/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:26:52 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/05 12:27:53 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *cube)
{
	static int	init;
	static int	last_x;
	int			dx;
	double		angle;
	double		sens;

	(void)y;
	if (!init)
	{
		init = 1;
		last_x = x;
		return (0);
	}
	dx = x - last_x;
	last_x = x;
	if (dx == 0)
		return (0);
	sens = 0.0025;
	angle = (double)dx * sens;
	rotate_angle(cube, angle);
	return (0);
}
