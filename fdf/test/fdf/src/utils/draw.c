/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:47:39 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 12:53:31 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_map(t_point **map, t_img *img, int color)
{
	int	curx;
	int	cury;

	curx = 0;
	while (map[curx])
	{
		cury = 0;
		while (!map[curx][cury].last)
		{
			if (map[curx + 1])
				img_line_put(img, map[curx][cury], map[curx + 1][cury], color);
			if (!map[curx][cury + 1].last)
				img_line_put(img, map[curx][cury], map[curx][cury + 1], color);
			cury++;
		}
		curx++;
	}
}

void	redraw(t_program *p)
{
	if (!p->updated)
	{
		img_init_background(&p->img, p->img.width, p->img.height, 0x000000);
		convert_to_iso(&p->map, 1);
		draw_map(p->map.m2d, &p->img, p->map.color);
		mlx_put_image_to_window(
			p->mlx, p->win, p->img.img, p->img.pos.x, p->img.pos.y);
	}
	p->updated = 1;
}

void	draw_square(t_program *p, t_point pos, int size, int color)
{
	int	x;
	int	y;

	x = pos.x;
	while (x < pos.x + size)
	{
		y = pos.y;
		while (y < pos.y + size)
		{
			mlx_pixel_put(p->mlx, p->win, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_rect(t_program *p, t_point top_left, t_point bm_right, int color)
{
	int	x;
	int	y;

	x = top_left.x;
	while (x < bm_right.x)
	{
		y = top_left.y;
		while (y < bm_right.y)
		{
			mlx_pixel_put(p->mlx, p->win, x, y, color);
			y++;
		}
		x++;
	}
}
