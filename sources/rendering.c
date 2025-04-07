/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:25:38 by tcassu            #+#    #+#             */
/*   Updated: 2025/04/07 18:18:45 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_buff(t_map *map)
{
	int	i;

	i = 0;
	if (!map->buff3d)
	{
		map->buff3d = malloc(map->size.y * sizeof(t_point *));
		while (i < map->size.y)
		{
			map->buff3d[i] = malloc(map->size.x * sizeof(t_point));
			i++;
		}
	}
}

int	get_rgb(float rgb, float zh, int zmax)
{
	if (zh <= 0)
		return (3105273);
	if (zh >= 0 && zh <= (zmax / 2))
		return (6008576);
	if (zh >= (zmax / 2))
		return (16777214);
	return (rgb + (zh * 0.5));
}

static void	calculate_coordinates(t_map *map, t_data *data, int x, int y)
{
	const int	z = map->heightmap[y][x];
	int			centered_x;
	int			centered_y;

	centered_x = x - map->size.x / 2;
	centered_y = y - map->size.y / 2;
	map->buff3d[y][x].x = (centered_x - centered_y) * data->zoom;
	map->buff3d[y][x].y = (centered_x + centered_y) * data->zoom / 2
		- (z * data->zoom / 5);
	map->buff3d[y][x].x += data->win_width / 2 + data->offset_x;
	map->buff3d[y][x].y += data->win_height / 2 + data->offset_y;
	map->buff3d[y][x].z = z;
	map->buff3d[y][x].color = get_rgb(data->rgb, z, map->zmax);
}

void	render(t_map *map, t_data *data)
{
	int	y;
	int	x;

	ft_buff(map);
	y = -1;
	while (++y < (int)map->size.y)
	{
		x = -1;
		while (++x < (int)map->size.x)
		{
			calculate_coordinates(map, data, x, y);
		}
	}
}

void	rend(t_mlx *mlx, t_data *data, t_map *map)
{
	ft_memset(mlx->img.data, 0,
		data->win_width * data->win_height * sizeof(int));
	render(&data->map, data);
	draw_all_lines(mlx, map, data);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.ptr, 0, 0);
}
