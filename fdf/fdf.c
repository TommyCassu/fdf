/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:04:26 by tcassu            #+#    #+#             */
/*   Updated: 2025/03/24 04:18:00 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"

#define MALLOC_ERROR	1
#define	SIDE_LEN		800
#define X				50
#define Y				50

void	init(t_data *data, char *filename)
{
	data->map.heightmap = NULL;
	ft_readmap(&data->map, filename);
	data->win_height = 1024;
	data->win_width = 1280;
}
int	main(int ac, char *av[])
{
	(void)ac;
	t_data	*data;
	//gestion erreur
	data = (t_data *)malloc(sizeof(t_data));
	init(data, av[1]);
	data->mlx.win = mlx_new_window(data->mlx.ptr,data->win_width,data->win_height,"FDF TCASSU");
	mlx_loop(data->mlx.ptr);
}