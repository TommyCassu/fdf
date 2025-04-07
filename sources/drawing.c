/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:46:23 by tcassu            #+#    #+#             */
/*   Updated: 2025/04/07 19:41:32 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static void	init_params(t_point p0, t_point p1, int d[2], int w[2])
{
	d[0] = abs(p1.x - p0.x);
	d[1] = abs(p1.y - p0.y);
	w[0] = (p1.x > p0.x) ? 1 : -1;
	w[1] = (p1.y > p0.y) ? 1 : -1;
}

static void	draw_line_higrad(t_point p0, t_point p1, int *img, t_data *data)
{
	int	d[2];
	int	w[2];
	int	err;
	int	col;

	col = ft_color(p0, p1);
	init_params(p0, p1, d, w);
	err = 2 * d[0] - d[1];
	while (p0.y != p1.y)
	{
		if (p0.x >= 0 && p0.x < data->win_width && p0.y >= 0
			&& p0.y < data->win_height)
			img[(p0.y * data->win_width + p0.x)] = col;
		if (err > 0)
		{
			p0.x += w[0];
			err -= 2 * d[1];
		}
		err += 2 * d[0];
		p0.y += w[1];
	}
}

static void	draw_line_lograd(t_point p0, t_point p1, int *img, t_data *data)
{
	int	d[2];
	int	w[2];
	int	err;
	int	col;

	col = ft_color(p0, p1);
	init_params(p0, p1, d, w);
	err = 2 * d[1] - d[0];
	while (p0.x != p1.x)
	{
		if (p0.x >= 0 && p0.x < data->win_width && p0.y >= 0
			&& p0.y < data->win_height)
			img[(p0.y * data->win_width + p0.x)] = col;
		if (err > 0)
		{
			p0.y += w[1];
			err -= 2 * d[0];
		}
		err += 2 * d[1];
		p0.x += w[0];
	}
}

static void	draw_line(t_point p0, t_point p1, t_mlx *mlx, t_data *data)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			draw_line_lograd(p1, p0, mlx->img.data, data);
		else
			draw_line_lograd(p0, p1, mlx->img.data, data);
	}
	else
	{
		if (p0.y > p1.y)
			draw_line_higrad(p1, p0, mlx->img.data, data);
		else
			draw_line_higrad(p0, p1, mlx->img.data, data);
	}
}

void	draw_all_lines(t_mlx *mlx, t_map *map, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->size.y)
	{
		x = 0;
		while (x < map->size.x)
		{
			if (x < map->size.x - 1)
				draw_line(map->buff3d[y][x], map->buff3d[y][x + 1], mlx, data);
			if (y < map->size.y - 1)
				draw_line(map->buff3d[y][x], map->buff3d[y + 1][x], mlx, data);
			x++;
		}
		y++;
	}
}
