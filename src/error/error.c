/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:36:42 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 12:20:26 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_error(const char *msg)
{
	ft_printf("Error\n%s\n", msg);
}

int	texture_path_error(t_texture *slot)
{
	free(slot->path);
	slot->path = NULL;
	return (print_error(ERR_BAD_TEXT_PATH), -1);
}
