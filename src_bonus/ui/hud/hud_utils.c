/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:21:18 by paalexan          #+#    #+#             */
/*   Updated: 2025/09/10 19:09:23 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

static char	*join_free(char *a, const char *b)
{
	char	*tmp;

	tmp = ft_strjoin(a, b);
	free(a);
	return (tmp);
}

char	*hud_make_counter_text(const t_game *cube)
{
	char	*a;
	char	*b;
	char	*msg;

	if (cube->collect.count <= 0)
		return (NULL);
	a = ft_itoa(cube->collect.collected);
	b = ft_itoa(cube->collect.count);
	if (!a || !b)
	{
		free(a);
		free(b);
		return (NULL);
	}
	msg = ft_strjoin("Collected ", a);
	if (!msg)
	{
		free(a);
		free(b);
		return (NULL);
	}
	msg = join_free(msg, "/");
	msg = join_free(msg, b);
	return (free(a), free(b), msg);
}
