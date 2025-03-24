/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:50:45 by tcassu            #+#    #+#             */
/*   Updated: 2025/03/24 03:32:58 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <fcntl.h>
#include <stdio.h>
#include "libft/libft.h"
#include <math.h>

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef struct	s_dimension
{
	int	x;
	int	y;
}				t_dimension;

typedef struct	s_map
{
	int			**heightmap;
	t_dimension	size;
	float		delta;
	float		median;
}				t_map;

typedef struct	s_data
{
	t_mlx		mlx;
	t_map		map;
	int			win_height;
	int			win_width;
}				t_data;

void	ft_readmap(t_map *map, char *filename);
#endif