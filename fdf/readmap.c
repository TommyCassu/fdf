/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:09:56 by tcassu            #+#    #+#             */
/*   Updated: 2025/03/24 04:14:34 by tcassu           ###   ########.fr       */
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
void	ft_readmap(t_map *map, char *filename)
{
	int	fd;
	
	map->size.y = 0;
	fd = open(filename, O_RDONLY);
	readfile(map, fd);
}

