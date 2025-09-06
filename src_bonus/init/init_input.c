/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:40:59 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 18:24:11 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void input_init(t_input *inp)
{
	inp->forward = 0;
	inp->backward = 0;
	inp->left = 0;
	inp->right = 0;
	inp->mouse_captured = 1;
	inp->last_x = SCR_W / 2;
	inp->last_y = SCR_H / 2;
	inp->mouse_angle = 0.0;
	inp->mouse_dy = 0.0;
	inp->sens = 0.001;
}
