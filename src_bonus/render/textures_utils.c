/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:16:47 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:36 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

unsigned int	get_texel(const t_img *img, int x, int y)
{
	char			*px;
	unsigned int	color;

	if (!img || !img->addr)
		return (0);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= img->w)
		x = img->w - 1;
	if (y >= img->h)
		y = img->h - 1;
	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	color = *(unsigned int *)px;
	return (color);
}

void	put_pixel_img(t_img *img, int x, int y, unsigned int color)
{
	char	*px;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	px = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)px = color;
}

static int	check_path_readable(const char *path)
{
	int	fd;

	if (!path)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

int	textures_precheck(t_game *cube)
{
	if (check_path_readable(cube->tex_no.path) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (check_path_readable(cube->tex_so.path) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (check_path_readable(cube->tex_we.path) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (check_path_readable(cube->tex_ea.path) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (cube->doors.len > 0)
	{
		if (check_path_readable(cube->tex_do.path) != 0)
			return (print_error(ERR_BAD_TEXT_PATH), -1);
	}
	if (check_path_readable(END_SCREEN_PATH) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (check_path_readable(PAUSE_SCREEN_PATH) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (check_path_readable(START_SCREEN_PATH) != 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	return (0);
}
