/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:32:52 by tcassu            #+#    #+#             */
/*   Updated: 2025/01/23 19:45:22 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define MAX(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)

float	mod(float i)
{
	return (i < 0) ? -i : i;
}
void	bresenham(int x, int y, float x1, float y1, s_point *data)
{
	float	x_step;
	float	y_step;
	int 	max;
	x_step = x1 - x;
	y_step = y1 - y;
	
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xffffff);
		x += x_step;
		y += y_step;
	}
}