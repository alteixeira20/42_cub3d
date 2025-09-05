/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:40:59 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/03 16:46:27 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	input_init(t_input *inp)
{
	inp->forward = 0;
	inp->backward = 0;
	inp->left = 0;
	inp->right = 0;
	inp->turn_l = 0;
	inp->turn_r = 0;
}
