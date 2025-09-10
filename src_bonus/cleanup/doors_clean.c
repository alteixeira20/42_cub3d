/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:10:48 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/09 16:37:29 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	clean_doors(t_doors *doors)
{
	if (doors->arr)
		free(doors->arr);
	doors->arr = NULL;
	doors->len = 0;
}
