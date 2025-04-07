/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:45:40 by tcassu            #+#    #+#             */
/*   Updated: 2025/04/07 19:36:40 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_exit(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	mlx_destroy_image(data->mlx.ptr, data->mlx.img.ptr);
	mlx_destroy_window(data->mlx.ptr, data->mlx.win);
	mlx_destroy_display(data->mlx.ptr);
	while (--data->map.size.y != (typeof(data->map.size.y)) - 1)
	{
		free(data->map.buff3d[data->map.size.y]);
		free(data->map.heightmap[data->map.size.y]);
	}
	free(data->map.buff3d);
	free(data->map.heightmap);
	free(data->mlx.ptr);
	free(data);
	exit(0);
}

int	keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == K_UP)
		data->offset_y += 10;
	else if (keycode == K_DWN)
		data->offset_y -= 10;
	else if (keycode == K_LFT)
		data->offset_x += 10;
	else if (keycode == K_RGT)
		data->offset_x -= 10;
	else if (keycode == K_W)
		data->zoom *= 1.25;
	else if (keycode == K_S)
		data->zoom /= 1.25;
	else if (keycode == K_ESC)
		ft_exit(data);
	return (1);
}

int	ft_color(t_point p0, t_point p1)
{
	if (p0.color > p1.color)
		return (p0.color);
	else
		return (p1.color);
}
