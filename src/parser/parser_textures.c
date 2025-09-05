/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:39:20 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/05 16:28:09 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_trimmed_end(const char *str, int start)
{
	int	end;

	end = ft_strlen(str);
	while (end > start && str[end - 1] == ' ')
		end--;
	return (end);
}

static int	copy_texture(const char	*str, int start, int end, char **out)
{
	int		len;
	int		i;
	char	*dst;

	len = end - start;
	dst = malloc(len + 1);
	if (!dst)
		return (print_error(ERR_ALLOC), -1);
	i = 0;
	while (i < len)
	{
		dst[i] = str[start + i];
		i++;
	}
	dst[len] = '\0';
	*out = dst;
	return (0);
}

static int	load_texture(t_texture *slot, const char *line, int id_len,
						const char *dup_err)
{
	int	start;
	int	end;
	int	fd;

	if (slot->is_set)
		return (print_error(dup_err), -1);
	start = skip_spaces(line, id_len);
	if (line[start] == '\0')
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	end = get_trimmed_end(line, start);
	if (end <= start)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	if (copy_texture(line, start, end, &slot->path) != 0)
		return (-1);
	fd = open(slot->path, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_BAD_TEXT_PATH), -1);
	close(fd);
	slot->is_set = true;
	return (1);
}

int	parse_texture(const char *line, t_game *game)
{
	int	i;

	if (!has_xpm_extension(line))
		return (-1);
	i = 0;
	i = skip_spaces(line, i);
	if (ft_strncmp(line + i, ID_NO, 2) == 0 && line[i + 2] == ' ')
		return (load_texture(&game->tex_no, line + i, 2,
				ERR_DUP_ID_NO));
	if (ft_strncmp(line + i, ID_SO, 2) == 0 && line[i + 2] == ' ')
		return (load_texture(&game->tex_so, line + i, 2,
				ERR_DUP_ID_SO));
	if (ft_strncmp(line + i, ID_WE, 2) == 0 && line[i + 2] == ' ')
		return (load_texture(&game->tex_we, line + i, 2,
				ERR_DUP_ID_WE));
	if (ft_strncmp(line + i, ID_EA, 2) == 0 && line[i + 2] == ' ')
		return (load_texture(&game->tex_ea, line + i, 2,
				ERR_DUP_ID_EA));
	return (0);
}
