/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:53:45 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 14:35:24 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_instructions(t_program *p)
{
	draw_rect(p, get_tpoint(0, 0),
		get_tpoint(p->width, p->img.pos.y), 0x151515);
	mlx_string_put(p->mlx, p->win, 10, 20, 0xFFFFFF, "FDF - Controls");
	mlx_string_put(p->mlx, p->win, 20, 35, 0xFFFFFF,
		"Left Click + Drag   -> Rotation");
	mlx_string_put(p->mlx, p->win, 20, 48, 0xFFFFFF,
		"Right Click + Drag  -> Translation");
	mlx_string_put(p->mlx, p->win, 20, 61, 0xFFFFFF,
		"Scroll              -> Zoom");
	mlx_string_put(p->mlx, p->win, 20, 74, 0xFFFFFF,
		"+/-                 -> Increase Z");
	mlx_string_put(p->mlx, p->win, 20, 87, 0xFFFFFF,
		"T                   -> Trimetric Projection");
	mlx_string_put(p->mlx, p->win, 20, 100, 0xFFFFFF,
		"R                   -> Dimetric Projection");
	mlx_string_put(p->mlx, p->win, 20, 113, 0xFFFFFF,
		"I                   -> Isometric Projection");
	draw_color_instructions(p);
	mlx_string_put(p->mlx, p->win, 500, 74, 0xFFFFFF,
		"Currently viewing : ");
	if (ft_strrchr(p->filename, '/') > 0)
		mlx_string_put(p->mlx, p->win, 640, 74, 0xFFFFFF,
			ft_strrchr(p->filename, '/') + 1);
	else
		mlx_string_put(p->mlx, p->win, 640, 74, 0xFFFFFF, p->filename);
}

void	draw_color_instructions(t_program *p)
{
	mlx_string_put(p->mlx, p->win, 360, 35, 0xFFFFFF, "1 -> White");
	mlx_string_put(p->mlx, p->win, 360, 48, 0xFFFFFF, "2 -> Green");
	mlx_string_put(p->mlx, p->win, 360, 61, 0xFFFFFF, "3 -> Red");
	mlx_string_put(p->mlx, p->win, 360, 74, 0xFFFFFF, "4 -> Blue");
	mlx_string_put(p->mlx, p->win, 360, 87, 0xFFFFFF, "5 -> Yellow");
	mlx_string_put(p->mlx, p->win, 360, 100, 0xFFFFFF, "6 -> Pink");
	mlx_string_put(p->mlx, p->win, 360, 113, 0xFFFFFF, "7 -> Grey");
	draw_square(p, get_tpoint(345, 28), 9, 0xFFFFFF);
	draw_square(p, get_tpoint(345, 41), 9, 0x008000);
	draw_square(p, get_tpoint(345, 54), 9, 0xFF0000);
	draw_square(p, get_tpoint(345, 67), 9, 0x1F75FE);
	draw_square(p, get_tpoint(345, 80), 9, 0xFFFF00);
	draw_square(p, get_tpoint(345, 93), 9, 0xFF1493);
	draw_square(p, get_tpoint(345, 106), 9, 0x808080);
}
