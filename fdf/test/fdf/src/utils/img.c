/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 09:40:39 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 13:03:50 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		cur;

	if (x >= img->width || x < 0 || y >= img->height || y < 0)
		return ;
	cur = img->pbits - 8;
	pixel = img->buffer + (y * img->lbytes + x * (img->pbits / 8));
	while (cur >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> cur) & 0xFF;
		else
			*pixel++ = (color >> (img->pbits - 8 - cur)) & 0xFF;
		cur -= 8;
	}
}

void	img_init_background(t_img *img, int width, int height, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			img_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	img_line_put(t_img *img, t_point p1, t_point p2, int color)
{
	double	dx;
	double	dy;
	int		pixels;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	while (pixels)
	{
		img_pixel_put(img, p1.x, p1.y, color);
		p1.x += dx;
		p1.y += dy;
		--pixels;
	}
}
