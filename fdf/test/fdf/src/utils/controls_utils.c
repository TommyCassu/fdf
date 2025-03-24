/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 12:37:28 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 12:38:44 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	set_isometric(t_program *p)
{
	p->map.rot_x = 0.7853982;
	p->map.rot_y = 0;
	p->map.rot_z = 0.6154729;
	p->map.z_increase = 0.2;
}

void	set_dimetric(t_program *p)
{
	p->map.rot_x = 0.7853982;
	p->map.rot_y = 0;
	p->map.rot_z = 0.4636467;
	p->map.z_increase = 0.2;
}

void	set_trimetric(t_program *p)
{
	p->map.rot_x = 1.047198;
	p->map.rot_y = 0;
	p->map.rot_z = 0.4642576;
	p->map.z_increase = 0.2;
}

int	set_color(int key, t_program *p)
{
	if (key == KEY_1)
		p->map.color = 0xFFFFFF;
	else if (key == KEY_2)
		p->map.color = 0x008000;
	else if (key == KEY_3)
		p->map.color = 0xFF0000;
	else if (key == KEY_4)
		p->map.color = 0x1F75FE;
	else if (key == KEY_5)
		p->map.color = 0xFFFF00;
	else if (key == KEY_6)
		p->map.color = 0xFF1493;
	else if (key == KEY_7)
		p->map.color = 0x808080;
	else
		return (0);
	return (1);
}
