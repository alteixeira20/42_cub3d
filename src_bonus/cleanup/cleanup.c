/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:29:58 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/09 16:37:54 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static void	clean_minimap(t_game *cube)
{
	if (cube->minimap.img_ptr)
	{
		mlx_destroy_image(cube->render.mlx, cube->minimap.img_ptr);
		cube->minimap.img_ptr = NULL;
	}
}

void	clean_game_setup(t_game *cube)
{
	clean_texture(&cube->tex_no);
	clean_texture(&cube->tex_so);
	clean_texture(&cube->tex_we);
	clean_texture(&cube->tex_ea);
	clean_map(&cube->map);
	cube->floor_color.is_set = false;
	cube->ceil_color.is_set = false;
	cube->player.is_set = false;
}

void	clean_game(t_game *cube)
{
	clean_texture(&cube->tex_no);
	clean_texture(&cube->tex_so);
	clean_texture(&cube->tex_we);
	clean_texture(&cube->tex_ea);
	clean_doors(&cube->doors);
	clean_map(&cube->map);
	cube->floor_color.is_set = false;
	cube->ceil_color.is_set = false;
	cube->player.is_set = false;
	textures_destroy(cube);
	clean_minimap(cube);
	render_destroy(cube);
}

void	clean_map_buffer(t_map_buffer *buf)
{
	int	i;

	i = 0;
	while (i < buf->count)
	{
		free(buf->items[i]);
		i++;
	}
	free(buf->items);
	buf->items = NULL;
	buf->count = 0;
	buf->capacity = 0;
}

void	clean_str_array(char **arr, int count)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
