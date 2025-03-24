#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"

#define MALLOC_ERROR	1
#define	SIDE_LEN		800
#define X				50
#define Y				50

/*
 * All the checks for errors like
 *
 * 	~if (vars.mlx == NULL) exit(1);
 *
 * are not written to not clog te code!
 * But u know this stuff is a necessary evil 😂
*/
int mouse_hook(int button, int x, int y, void *param)
{
    t_img *img = (t_img *)param;

    if (button == 4) // Scroll up
        img->zoom *= 1.1;
    else if (button == 5) // Scroll down
        img->zoom /= 1.1;
    return (0);
}

void iso(int *x, int *y, int z, t_img *img)
{
    int old_x = *x;
    int old_y = *y;
    *x = (int)((old_x - old_y) * cos(0.523599) * img->zoom);
    *y = (int)((old_x + old_y) * sin(0.523599) * img->zoom - z);
    
    // Ajouter un offset pour centrer
    *x += 1000 / 2;
    *y += 1000 / 2;
}

void    my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->img_pixels_ptr + (y * data->line_len + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color, int z)
{
	iso(&x0, &y0, z, img);
    iso(&x1, &y1, z, img);

	int diffX = abs(x1 - x0);
    int diffY = -abs(y1 - y0);
    int sensX = x0 < x1 ? 1 : -1;
    int sensY = y0 < y1 ? 1 : -1;
    int err = diffX + diffY;
    int e2;

    while (1)
    {
        my_mlx_pixel_put(img, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= diffY)
        {
            err += diffY;
            x0 += sensX;
        }
        if (e2 <= diffX)
        {
            err += diffX;
            y0 += sensY;
        }
    }
}
int	main()
{
	t_var	vars;
	t_img	img;
	s_point	**fdf;


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx,
								1000,
								1000,
								"FDF TCASSU");
	img.img_ptr = mlx_new_image(vars.mlx, 1000, 1000);
	img.zoom = 3.0;
    img.img_pixels_ptr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_len,
                                 &img.endian);
	fdf = parsing();
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < 19)
	{
		j = 0;
		while (j < 11)
		{
			x = i * 10;
			y = j * 10;
			if (j < 10) {
				if ((fdf[j][i].z) > 1)
					draw_line(&img, x, y, x, (j+1)*10, 0x00FF0000, fdf[j][i].z);
				else
					draw_line(&img, x, y, x, (j+1)*10, 0x00FFFFFF, fdf[j][i].z);
			}
			if (i < 18) {
				if ((fdf[j][i].z) > 1)
					draw_line(&img, x, y, (i+1)*10, y, 0x00FF0000, fdf[j][i].z);
				else
					draw_line(&img, x, y, (i+1)*10, y, 0x00FFFFFF, fdf[j][i].z);
			}
			j++;
		}
		i++;
	}
    mlx_put_image_to_window(vars.mlx, vars.win, img.img_ptr, 0, 0);
	mlx_mouse_hook(vars.win, mouse_hook, &img);
	mlx_loop(vars.mlx);
}