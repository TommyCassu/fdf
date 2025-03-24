/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:24:10 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 13:03:59 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_3Dpoint	*get_rotx(t_map mapd)
{
	t_3Dpoint	*rot;

	rot = (t_3Dpoint *)malloc(sizeof(t_3Dpoint) * 3);
	if (!rot)
		exit(EXIT_FAILURE);
	rot[0].x = 1;
	rot[0].y = 0;
	rot[0].z = 0;
	rot[1].x = 0;
	rot[1].y = cos(mapd.rot_x);
	rot[1].z = -sin(mapd.rot_x);
	rot[2].x = 0;
	rot[2].y = sin(mapd.rot_x);
	rot[2].z = cos(mapd.rot_x);
	return (rot);
}

static t_3Dpoint	*get_roty(t_map mapd)
{
	t_3Dpoint	*rot;

	rot = (t_3Dpoint *)malloc(sizeof(t_3Dpoint) * 3);
	if (!rot)
		exit(EXIT_FAILURE);
	rot[0].x = cos(mapd.rot_y);
	rot[0].y = 0;
	rot[0].z = sin(mapd.rot_y);
	rot[1].x = 0;
	rot[1].y = 1;
	rot[1].z = 0;
	rot[2].x = -sin(mapd.rot_y);
	rot[2].y = 0;
	rot[2].z = cos(mapd.rot_y);
	return (rot);
}

static t_3Dpoint	*get_rotz(t_map mapd)
{
	t_3Dpoint	*rot;

	rot = (t_3Dpoint *)malloc(sizeof(t_3Dpoint) * 3);
	if (!rot)
		exit(EXIT_FAILURE);
	rot[0].x = cos(mapd.rot_z);
	rot[0].y = -sin(mapd.rot_z);
	rot[0].z = 0;
	rot[1].x = sin(mapd.rot_z);
	rot[1].y = cos(mapd.rot_z);
	rot[1].z = 0;
	rot[2].x = 0;
	rot[2].y = 0;
	rot[2].z = 1;
	return (rot);
}

t_3Dpoint	**get_rotxyz(t_map mapd)
{
	t_3Dpoint	**rots;

	rots = (t_3Dpoint **)malloc(sizeof(t_3Dpoint *) * 3);
	if (!rots)
		exit(EXIT_FAILURE);
	rots[0] = get_rotx(mapd);
	rots[1] = get_roty(mapd);
	rots[2] = get_rotz(mapd);
	return (rots);
}

void	*free_rot(t_3Dpoint **rot)
{
	free(rot[0]);
	free(rot[1]);
	free(rot[2]);
	free(rot);
	return (NULL);
}
