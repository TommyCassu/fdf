/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 10:02:48 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/06 10:20:52 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../../libft/libft.h"
# include "../../mlx/mlx.h"
# include "keys.h"

typedef struct s_point
{
	double	x;
	double	y;
	int		last;
}	t_point;

typedef struct s_3Dpoint
{
	double	x;
	double	y;
	double	z;
	int		last;
}	t_3Dpoint;

typedef struct s_img
{
	void	*img;
	int		pbits;
	int		lbytes;
	int		endian;
	char	*buffer;
	int		width;
	int		height;
	t_point	pos;
}	t_img;

typedef struct s_map
{
	t_point		**m2d;
	t_3Dpoint	**m3d;
	int			t_x;
	int			t_y;
	double		rot_x;
	double		rot_y;
	double		rot_z;
	double		z_increase;
	double		zoom;
	int			color;
}	t_map;

typedef struct s_program
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_img	img;
	t_map	map;
	t_point	mouse;
	int		updated;
	int		mouse_right;
	int		mouse_left;
	char	*filename;
}	t_program;

// controls_utils.c
void		set_isometric(t_program *p);
void		set_dimetric(t_program *p);
void		set_trimetric(t_program *p);
int			set_color(int key, t_program *p);
// controls.c
int			deal_key(int key, void *param);
int			button_press(int key, int x, int y, void *param);
int			button_release(int key, int x, int y, void *param);
int			mouse_motion(int x, int y, void *param);
// convert_utils.c
void		*free_m2d(t_point ***m2d, int is_allocated);
int			get_3dmap_width(t_3Dpoint **map_3d);
int			get_3dmap_height(t_3Dpoint **map_3d);
// convert.c
t_point		**alloc_2dmap_array(t_3Dpoint **map_3d);
void		convert_to_iso(t_map *mapd, int is_allocated);
// draw.c
void		draw_map(t_point **map, t_img *img, int color);
void		redraw(t_program *p);
void		draw_square(t_program *p, t_point pos, int size, int color);
void		draw_rect(t_program *p, t_point tl, t_point br, int color);
// img.c
void		img_pixel_put(t_img *img, int x, int y, int color);
void		img_init_background(t_img *img, int width, int height, int color);
void		img_line_put(t_img *img, t_point p1, t_point p2, int color);
// instructions.c
void		draw_instructions(t_program *p);
void		draw_color_instructions(t_program *p);
// map.c
void		parse_map_file(char *filename, t_3Dpoint ***map);
// matrix.c
t_3Dpoint	matmul(t_3Dpoint mul[3], t_3Dpoint mat);
// rotation_matrix.c
t_3Dpoint	**get_rotxyz(t_map mapd);
void		*free_rot(t_3Dpoint **rot);
// utils.c
t_point		get_tpoint(int x, int y);
#endif
