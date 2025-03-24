/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:33:41 by tcassu            #+#    #+#             */
/*   Updated: 2025/02/11 16:32:30 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

int	get_height()
{
	char	*line;
	int 	fd;
	int		height;

	fd = open("test.txt", O_RDONLY, 0);
	if (fd == -1)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return (1);
    }
	height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}
int	get_width()
{
	
	char	*line;
	char	**words;
	int		fd;
	int 	i;
	
	i = 0;
	fd = open("test.txt", O_RDONLY, 0);
	if (fd == -1)
	{
        printf("Erreur lors de l'ouverture du fichier\n");
        return (1);
    }
	line = get_next_line(fd);
	words = ft_split(line, ' ');
	free(line);
	while ((line = get_next_line(fd)) != NULL)
		free(line);
	while(words[i] != 0)
		free(words[i++]);
	free(words);
	close(fd);
	return (i);
}
void	alloc_3dmap(t_point3d ***map, int height, int width)
{
	int	xi;
	int	yi;
	
	yi = 0;
	*map = (t_point3d **)malloc(sizeof(t_point3d *) * (height + 1));
	(*map)[height] = 0;
	while (yi < height)
	{
		(*map)[yi] = (t_point3d *)malloc(sizeof(t_point3d) * (width + 1));
		xi = 0;
		while (xi < width)
		{
			(*map)[yi][xi].x = xi;
			(*map)[yi][xi].y = yi;
			xi++;
		}
		yi++;
	}
}
int	main()
{
	t_point3d	**fdf;
	int 	height;
	int 	width;
	int h;
	int w;
	int i;
	int fd;
	char *line;
	
	height = get_height();
	width = get_width();
	alloc_3dmap(&fdf, height, width);
	h = 0;
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
			
	}
	return (fdf);
}