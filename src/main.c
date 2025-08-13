/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 00:08:15 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 17:05:19 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;
	int		status;

	if (argc != 2)
	{
		print_error(ERR_USAGE);
		return (1);
	}
	if (!has_cub_extension(argv[1]))
	{
		print_error(ERR_INVALID_EXT);
		return (1);
	}
	game_init(&game);
	status = parse_all(argv[1], &game);
	if (status != 0)
	{
		clean_game(&game);
		return (1);
	}
	print_parse(&game);
	clean_game(&game);
	return (0);
}
