/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:18:29 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/11 17:22:18 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	check_key_frame_path(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

static int	load_one_frame(void *mlx, const char *path, t_img *out)
{
	out->img = NULL;
	out->addr = NULL;
	out->img = mlx_xpm_file_to_image(mlx, (char *)path, &out->w, &out->h);
	if (!out->img)
		return (-1);
	out->addr = mlx_get_data_addr(out->img, &out->bpp,
			&out->line_len, &out->endian);
	if (!out->addr)
		return (-1);
	return (0);
}

static int	make_key_path(int idx, char **out, const char *base)
{
	char	*tmp;
	char	*num;
	char	*pre;
	char	*path;

	tmp = NULL;
	num = NULL;
	pre = NULL;
	path = NULL;
	tmp = ft_strjoin(base, "key_frame-");
	if (!tmp)
		return (-1);
	num = ft_itoa(idx);
	if (!num)
		return (free3(NULL, &tmp, NULL), -1);
	pre = ft_strjoin(tmp, num);
	if (!pre)
		return (free3(NULL, &tmp, &num), -1);
	path = ft_strjoin(pre, ".xpm");
	if (!path)
		return (free3(NULL, &tmp, &num), free(pre), -1);
	free3(NULL, &tmp, &num);
	free(pre);
	*out = path;
	return (0);
}

int	keys_precheck(t_game *cube)
{
	int		i;
	int		r;
	char	*base;
	char	*path;

	if (cube->collect.count <= 0)
		return (0);
	base = ft_strdup("assets/key/");
	if (!base)
		return (print_error(ERR_ALLOC), -1);
	i = 0;
	while (i < KEY_FRAME_COUNT)
	{
		path = NULL;
		r = make_key_path(i, &path, base);
		if (r != 0)
			return (free(base), print_error(ERR_ALLOC), -1);
		r = check_key_frame_path(path);
		free(path);
		if (r != 0)
			return (free(base), print_error(ERR_BAD_TEXT_PATH), -1);
		i++;
	}
	free(base);
	return (0);
}

int	keys_load(t_game *cube)
{
	int		i;
	char	*path;
	int		r;
	char	*base;

	i = 0;
	path = NULL;
	base = ft_strdup("assets/key/");
	if (!base)
		return (print_error(ERR_ALLOC), -1);
	while (i < KEY_FRAME_COUNT)
	{
		r = make_key_path(i, &path, base);
		if (r != 0)
			return (print_error(ERR_ALLOC), -1);
		r = load_one_frame(cube->render.mlx, path,
				&cube->collect.key_frames[i]);
		free(path);
		path = NULL;
		if (r != 0)
			return (-1);
		i = i + 1;
	}
	free(base);
	return (0);
}
