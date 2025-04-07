/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:50:45 by tcassu            #+#    #+#             */
/*   Updated: 2025/04/07 19:42:00 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <math.h>
# include <stdint.h>

#include <stdint.h>

# ifdef __linux__
#  define K_UP 65362
#  define K_DWN 65364
#  define K_LFT 65361
#  define K_RGT 65363
#  define K_Q 113
#  define K_E 101
#  define K_W 119
#  define K_S 115
#  define K_A 97
#  define K_D 100
#  define K_ESC 65307
# endif

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			line_s;
	int			bpp;
	int			endian;
}				t_img;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct s_dimension
{
	int	x;
	int	y;
}				t_dimension;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_map
{
	int				**heightmap;
	t_point			**buff3d;
	t_dimension		size;
	float			delta;
	float			median;
	int				zmax;
	int				zmin;
}				t_map;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	float		zoom;
	int			offset_x;
	int			offset_y;
	int			rgb;
	float		zh;
	int			win_height;
	int			win_width;
}				t_data;

void	ft_readmap(t_map *map, char *filename);
void	rend(t_mlx *mlx, t_data *data, t_map *map);
void	draw_all_lines(t_mlx *mlx, t_map *map, t_data *data);
int		ft_color(t_point p0, t_point p1);
int		keypress(int keycode, void *param);
int		ft_exit(void *param);
#endif