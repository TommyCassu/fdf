/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:19:25 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/06 10:24:51 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	deal_key(int key, void *param)
{
	t_program	*p;

	p = param;
	if (key == KEY_I)
		set_isometric(p);
	else if (key == KEY_R)
		set_dimetric(p);
	else if (key == KEY_T)
		set_trimetric(p);
	else if (key == KEY_PLUS)
		p->map.z_increase += 0.2;
	else if (key == KEY_MINUS)
		p->map.z_increase -= 0.2;
	else if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if (!set_color(key, p))
	{
		p->updated = 1;
		return (0);
	}
	p->updated = 0;
	return (0);
}

int	button_press(int key, int x, int y, void *param)
{
	t_program	*p;

	p = param;
	if (key == MOUSE_LEFT)
		p->mouse_left = 1;
	else if (key == MOUSE_RIGHT)
		p->mouse_right = 1;
	else
	{
		if (key == WHEEL_UP)
			p->map.zoom *= 1.3;
		else if (key == WHEEL_DOWN)
			p->map.zoom /= 1.3;
		if (key == WHEEL_UP || key == WHEEL_DOWN)
			p->updated = 0;
	}
	p->mouse.x = x;
	p->mouse.y = y;
	return (0);
}

int	button_release(int key, int x, int y, void *param)
{
	t_program	*p;

	p = param;
	if (key == MOUSE_LEFT)
		p->mouse_left = 0;
	else if (key == MOUSE_RIGHT)
		p->mouse_right = 0;
	p->mouse.x = x;
	p->mouse.y = y;
	return (0);
}

int	mouse_motion(int x, int y, void *param)
{
	t_program	*p;

	p = param;
	if (p->mouse_right)
	{
		p->map.rot_x += (p->mouse.y - y) / 150;
		p->map.rot_y += (x - p->mouse.x) / 150;
	}
	if (p->mouse_left)
	{
		p->map.t_x += x - p->mouse.x;
		p->map.t_y += y - p->mouse.y;
	}
	if (p->mouse_left || p->mouse_right)
	{
		p->mouse.x = x;
		p->mouse.y = y;
		p->updated = 0;
	}
	return (0);
}
