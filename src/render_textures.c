/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:57:08 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/03 17:56:09 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	load_one_tex(void *mlx, const char *path, t_img *out)
{
	out->img = mlx_xpm_file_to_image(mlx, (char *)path, &out->w, &out->h);
	if (!out->img)
		return (-1);
	out->addr = mlx_get_data_addr(out->img, &out->bpp, &out->line_len,
			&out->endian);
	if (!out->addr)
		return (-1);
	return (0);
}

static void	destroy_one_tex(void *mlx, t_img *img)
{
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->w = 0;
	img->h = 0;
}

static int	load_all_paths(t_game *cube)
{
	if (load_one_tex(cube->render.mlx, cube->tex_no.path,
			&cube->tex_rt[0].img) != 0)
		return (-1);
	if (load_one_tex(cube->render.mlx, cube->tex_so.path,
			&cube->tex_rt[1].img) != 0)
		return (-1);
	if (load_one_tex(cube->render.mlx, cube->tex_we.path,
			&cube->tex_rt[2].img) != 0)
		return (-1);
	if (load_one_tex(cube->render.mlx, cube->tex_ea.path,
			&cube->tex_rt[3].img) != 0)
		return (-1);
	return (0);
}

int	textures_load(t_game *cube)
{
	if (!cube->render.mlx)
		return (-1);
	if (!cube->tex_no.path || !cube->tex_so.path
		|| !cube->tex_we.path || !cube->tex_ea.path)
		return (-1);
	if (load_all_paths(cube) != 0)
	{
		textures_destroy(cube);
		return (-1);
	}
	return (0);
}

void	textures_destroy(t_game *cube)
{
	destroy_one_tex(cube->render.mlx, &cube->tex_rt[0].img);
	destroy_one_tex(cube->render.mlx, &cube->tex_rt[1].img);
	destroy_one_tex(cube->render.mlx, &cube->tex_rt[2].img);
	destroy_one_tex(cube->render.mlx, &cube->tex_rt[3].img);
}
