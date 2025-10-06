/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 11:12:51 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/12 17:34:30 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	color_get_value(const char *line, int i, int *out)
{
	long	val;

	i = skip_spaces(line, i);
	if (!ft_isdigit(line[i]))
		return (-1);
	val = 0;
	while (ft_isdigit(line[i]))
	{
		int	digit;

		digit = line[i] - '0';
		if (val > 25 || (val == 25 && digit > 5))
			return (-1);
		val = val * 10 + digit;
		i++;
	}
	*out = (int)val;
	i = skip_spaces(line, i);
	return (i);
}

static int	parse_component(const char *line, int i,
							int *value, bool expect_comma)
{
	i = color_get_value(line, i, value);
	if (i < 0)
		return (-1);
	if (expect_comma)
	{
		if (line[i] != ',')
			return (-1);
		i++;
	}
	return (i);
}

static int	color_assign(const char *line, t_color *dst, const char *dup_err)
{
	int			i;
	int			r;
	int			g;
	int			b;

	if (dst->is_set)
		return (print_error(dup_err), -1);
	i = 1;
	i = parse_component(line, i, &r, true);
	if (i < 0)
		return (print_error(ERR_BAD_COLOR), -1);
	i = parse_component(line, i, &g, true);
	if (i < 0)
		return (print_error(ERR_BAD_COLOR), -1);
	i = parse_component(line, i, &b, false);
	if (i < 0)
		return (print_error(ERR_BAD_COLOR), -1);
	i = skip_spaces(line, i);
	if (line[i] != '\0')
		return (print_error(ERR_BAD_COLOR), -1);
	dst->r = r;
	dst->g = g;
	dst->b = b;
	dst->argb = (0xFF << 24) | (r << 16) | (g << 8) | b;
	dst->is_set = true;
	return (0);
}

int	parse_color(const char *line, t_game *cube)
{
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (color_assign(line, &cube->floor_color, ERR_DUP_ID_F) != 0)
			return (-1);
		return (1);
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (color_assign(line, &cube->ceil_color, ERR_DUP_ID_C) != 0)
			return (-1);
		return (1);
	}
	return (0);
}
