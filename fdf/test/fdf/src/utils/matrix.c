/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:25:24 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/05 10:25:48 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_3Dpoint	matmul(t_3Dpoint mul[3], t_3Dpoint mat)
{
	t_3Dpoint	result;

	result.x = mat.x * mul[0].x + mat.y * mul[0].y + mat.z * mul[0].z;
	result.y = mat.x * mul[1].x + mat.y * mul[1].y + mat.z * mul[1].z;
	result.z = mat.x * mul[2].x + mat.y * mul[2].y + mat.z * mul[2].z;
	return (result);
}
