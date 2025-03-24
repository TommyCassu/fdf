/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:21 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 13:04:17 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_point	**alloc_2dmap_array(t_3Dpoint **map_3d)
{
	int		curh;
	int		curw;
	int		width;
	int		height;
	t_point	**map;

	width = get_3dmap_width(map_3d);
	height = get_3dmap_height(map_3d);
	curh = 0;
	map = (t_point **)malloc(sizeof(t_point *) * (height + 1));
	if (!map)
		exit(EXIT_FAILURE);
	map[height] = 0;
	while (curh < height)
	{
		map[curh] = (t_point *)malloc(sizeof(t_point) * (width));
		if (!map[curh])
			exit(EXIT_FAILURE);
		curw = 0;
		while (curw < width - 1)
			map[curh][curw++].last = 0;
		map[curh][curw].last = 1;
		curh++;
	}
	return (map);
}

void	convert_to_iso(t_map *mapd, int is_allocated)
{
	int				curw;
	int				curh;
	t_3Dpoint		**rots;
	t_3Dpoint		proj;

	free_m2d(&mapd->m2d, is_allocated);
	mapd->m2d = alloc_2dmap_array(mapd->m3d);
	rots = get_rotxyz(*mapd);
	if (!mapd->m2d || !rots)
		exit(EXIT_FAILURE);
	curh = 0;
	while (mapd->m2d[curh])
	{
		curw = 0;
		while (!mapd->m2d[curh][curw].last)
		{
			proj = mapd->m3d[curh][curw];
			proj.z = mapd->m3d[curh][curw].z * mapd->z_increase;
			proj = matmul(rots[2], matmul(rots[1], matmul(rots[0], proj)));
			mapd->m2d[curh][curw].x = proj.x * mapd->zoom + mapd->t_x;
			mapd->m2d[curh][curw++].y = proj.y * mapd->zoom + mapd->t_y;
		}
		curh++;
	}
	free_rot(rots);
}
