/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:41:39 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/12 18:05:10 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_3dmap_width(t_3Dpoint **map_3d)
{
	int	width;

	width = 0;
	while (map_3d[0] && !map_3d[0][width].last)
		width++;
	return (width);
}

int	get_3dmap_height(t_3Dpoint **map_3d)
{
	int	height;

	height = 0;
	while (map_3d[height])
		height++;
	return (height);
}

void	*free_m2d(t_point ***m2d, int is_allocated)
{
	int	curh;

	if (is_allocated)
	{
		curh = 0;
		while ((*m2d)[curh])
		{
			free((*m2d)[curh]);
			curh++;
		}
		free((*m2d));
	}
	return (NULL);
}
