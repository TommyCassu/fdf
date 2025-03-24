/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:55:46 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/18 12:41:20 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fdf.h"

int	close_mlx(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	render(void *params)
{
	t_program	*p;

	p = params;
	redraw(p);
	return (0);
}

void	init_program(t_program *p)
{
	p->width = 1920;
	p->height = 1080;
	p->img.width = p->width;
	p->img.height = p->height - 128;
	p->img.pos.x = 0;
	p->img.pos.y = 128;
	p->mouse.x = 0;
	p->mouse.y = 0;
	p->mouse_right = 0;
	p->mouse_left = 0;
	p->updated = 0;
	p->map.t_x = 250;
	p->map.t_y = 250;
	p->map.zoom = 6;
	p->map.rot_x = 0;
	p->map.rot_y = 0;
	p->map.rot_z = 0;
	p->map.color = 0xFFFFFF;
	p->map.z_increase = 0.2;
	set_dimetric(p);
}

char	*get_check_map_file(int argc, char **argv, t_program *p)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd("Usage : fdf <map file>\n", 1);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		ft_putstr_fd("Can't read file : ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("\n", 1);
		exit(EXIT_FAILURE);
	}
	p->filename = argv[1];
	return (argv[1]);
}

int	main(int argc, char **argv)
{
	t_program	p;

	init_program(&p);
	parse_map_file(get_check_map_file(argc, argv, &p), &p.map.m3d);
	p.mlx = mlx_init();
	if (!p.mlx)
		exit(EXIT_FAILURE);
	p.win = mlx_new_window(p.mlx, p.width, p.height, "FDF ocartier");
	if (!p.win)
		exit(EXIT_FAILURE);
	p.img.img = mlx_new_image(p.mlx, p.img.width, p.img.height);
	if (!p.img.img)
		exit(EXIT_FAILURE);
	p.img.buffer = mlx_get_data_addr(
			p.img.img, &p.img.pbits, &p.img.lbytes, &p.img.endian);
	p.map.m2d = alloc_2dmap_array(p.map.m3d);
	draw_instructions(&p);
	render(&p);
	mlx_loop_hook(p.mlx, render, &p);
	mlx_key_hook(p.win, deal_key, &p);
	mlx_hook(p.win, ON_DESTROY, 0L, close_mlx, &p);
	mlx_hook(p.win, ON_MOTION_NOTIFY, 0L, mouse_motion, &p);
	mlx_hook(p.win, ON_BUTTON_PRESS, 0L, button_press, &p);
	mlx_hook(p.win, ON_BUTTON_RELEASE, 0L, button_release, &p);
	mlx_loop(p.mlx);
}
