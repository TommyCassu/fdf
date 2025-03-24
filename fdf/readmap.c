/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:56 by tcassu            #+#    #+#             */
/*   Updated: 2025/03/24 16:13:28 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
#include <stdint.h>

# define PX_END_OF_LINE	((uint16_t)-1)

void	ft_freetab(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

int	ft_fill_line(char **data, t_map *map)
{
	int	i;
	int	height;
	char	**tmp;
	
	i = 0;
	tmp = data;
	while (*tmp)
		++tmp;
	map->heightmap[map->size.y] = malloc((tmp - data + 1) * sizeof(int));

	while(data[i])
	{
		height = ft_atoi(data[i]);
		map->heightmap[map->size.y][i] = height;
		i++;
	}
	map->heightmap[map->size.y][i] = PX_END_OF_LINE;
	return (i);
}

t_map	*readfile(t_map *map, int fd)
{
	char	**tab;
	char	*line;
	int		len;
	
	while((line = get_next_line(fd)))
	{
		tab = ft_split(line, ' ');
		len = ft_fill_line(tab, map);
		if (len > map->size.x)
			map->size.x = len;
		++map->size.y;
		free(line);
		ft_freetab(tab);
	}
	return (map);
}
int	ft_mappingHeight(char *filename)
{
	int	i;
	int	fd;
	char	*line;
	
	fd = open(filename, O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		i++;
		free(line);
	}
	return (i);
}
void	ft_readmap(t_map *map, char *filename)
{
	int	fd;
	
	map->size.y = ft_mappingHeight(filename);
	map->heightmap = malloc(sizeof(int *) * map->size.y);
	fd = open(filename, O_RDONLY);
	map->size.y = 0;
	readfile(map, fd);
}
/* 
#include "fdf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    t_map map;
    int i, j;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Initialisation de la map
    map.size.x = 0;
    map.size.y = 0;
    map.heightmap = NULL;

    // Lecture de la map
    ft_readmap(&map, argv[1]);

    // Affichage des résultats
    printf("Map size: %d x %d\n", map.size.x, map.size.y);
    printf("Heightmap:\n");
    for (i = 0; i < map.size.y; i++)
    {
        for (j = 0; map.heightmap[i][j] != PX_END_OF_LINE; j++)
        {
            printf("%3d ", map.heightmap[i][j]);
        }
        printf("\n");
    }

    // Libération de la mémoire
    for (i = 0; i < map.size.y; i++)
    {
        free(map.heightmap[i]);
    }
    free(map.heightmap);

    return 0;
}
*/
