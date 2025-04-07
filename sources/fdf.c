/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:04:26 by tcassu            #+#    #+#             */
/*   Updated: 2025/04/07 19:41:00 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	init_mlx(t_mlx *mlx, t_data *data)
{
	mlx->ptr = mlx_init();
	data->mlx.ptr = mlx->ptr;
	data->mlx.win = mlx_new_window(data->mlx.ptr, data->win_width,
			data->win_height, "FDF TCASSU");
	mlx->img.ptr = mlx_new_image(mlx->ptr, data->win_width, data->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.ptr, &mlx->img.bpp,
			&mlx->img.line_s, &mlx->img.endian);
}

void	init(t_data *data, char *filename)
{
	data->map.heightmap = NULL;
	data->map.buff3d = NULL;
	ft_readmap(&data->map, filename);
	data->zoom = 3.0;
	data->offset_x = 0;
	data->offset_y = 0;
	data->rgb = 0x055900;
	data->zh = 1.;
	data->win_height = 1024;
	data->win_width = 1280;
	data->mlx.ptr = NULL;
	init_mlx(&data->mlx, data);
}

int	exec_render(t_data *d)
{
	rend(&d->mlx, d, &d->map);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	(void)ac;
	data = (t_data *)malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	init(data, av[1]);
	rend(&data->mlx, data, &data->map);
	mlx_hook(data->mlx.win, 2, 1L, &keypress, data);
	mlx_loop_hook(data->mlx.ptr, &exec_render, data);
	mlx_hook(data->mlx.win, 17, 0, ft_exit, data);
	mlx_loop(data->mlx.ptr);
}
