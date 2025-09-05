/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:19:18 by jopedro-          #+#    #+#             */
/*   Updated: 2025/09/05 16:20:13 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static int	setup_after_parse(t_game *cube)
{
	if (render_init(cube) != 0)
		return (-1);
	if (textures_load(cube) != 0)
	{
		render_destroy(cube);
		return (-1);
	}
	return (0);
}

static void	register_hooks(t_game *cube)
{
	mlx_hook(cube->render.win, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->render.win, 3, 1L << 1, key_release, cube);
	mlx_hook(cube->render.win, 17, 0, win_close, cube);
	mlx_loop_hook(cube->render.mlx, game_loop, cube);
}

static int	startup(t_game *cube, const char *path)
{
	game_init(cube);
	if (!has_cub_extension(path))
		return (print_error(ERR_INVALID_EXT), -1);
	if (parse_all(path, cube) != 0)
		return (-1);
	if (setup_after_parse(cube) != 0)
		return (-1);
	register_hooks(cube);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	cube;

	if (argc != 2)
		return (print_error(ERR_USAGE), 1);
	if (startup(&cube, argv[1]) != 0)
		return (clean_game_setup(&cube), 1);
	mlx_loop(cube.render.mlx);
	clean_game(&cube);
	return (0);
}
