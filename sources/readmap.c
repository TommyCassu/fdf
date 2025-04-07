/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:56 by tcassu            #+#    #+#             */
/*   Updated: 2025/04/07 19:42:09 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
	int		i;
	int		height;
	char	**tmp;

	i = 0;
	tmp = data;
	while (*tmp)
		++tmp;
	map->heightmap[map->size.y] = malloc((tmp - data + 1) * sizeof(int));
	while (data[i])
	{
		height = ft_atoi(data[i]);
		map->heightmap[map->size.y][i] = height;
		if (map->zmin > height)
			map->zmin = height;
		if (map->zmax < height)
			map->zmax = height;
		i++;
	}
	map->heightmap[map->size.y][i] = '\0';
	return (i);
}

t_map	*readfile(t_map *map, int fd)
{
	char	**tab;
	char	*line;
	int		len;

	line = get_next_line(fd);
	while (line != NULL)
	{
		tab = ft_split(line, ' ');
		len = ft_fill_line(tab, map);
		if (len && len > map->size.x)
			map->size.x = len;
		++map->size.y;
		free(line);
		ft_freetab(tab);
		line = get_next_line(fd);
	}
	return (map);
}

int	ft_mappingheight(char *filename)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

void	ft_readmap(t_map *map, char *filename)
{
	int	fd;

	map->zmin = 0;
	map->zmax = 0;
	map->size.y = ft_mappingheight(filename);
	map->heightmap = malloc(sizeof(int *) * map->size.y);
	fd = open(filename, O_RDONLY);
	map->size.y = 0;
	readfile(map, fd);
}
