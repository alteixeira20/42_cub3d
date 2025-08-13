/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:58:55 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/13 15:34:40 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	line_is_spaces_only(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int	line_is_map_content(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			return (0);
		if (!ft_strchr(MAP_CHARS, str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	skip_spaces(const char *str, int i)
{
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int	ids_complete(t_game *game)
{
	if (!game->tex_no.path || game->tex_no.path[0] == '\0')
		return (0);
	if (!game->tex_so.path || game->tex_so.path[0] == '\0')
		return (0);
	if (!game->tex_we.path || game->tex_we.path[0] == '\0')
		return (0);
	if (!game->tex_ea.path || game->tex_ea.path[0] == '\0')
		return (0);
	if (!game->floor_color.is_set)
		return (0);
	if (!game->ceil_color.is_set)
		return (0);
	return (1);
}
