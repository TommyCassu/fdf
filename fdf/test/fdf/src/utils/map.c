/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 15:51:49 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/12 18:05:30 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	get_map_height(char *filename)
{
	int		lines_num;
	int		fd;
	char	*line;

	lines_num = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd, GNL_KEEP);
	while (line)
	{
		lines_num++;
		free(line);
		line = get_next_line(fd, GNL_KEEP);
	}
	close(fd);
	return (lines_num);
}

static int	get_map_width(char *filename)
{
	int		width;
	int		fd;
	char	*line;
	int		cur;

	width = 1;
	cur = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd, GNL_CLEAR);
	while (line && line[cur])
	{
		if ((line[cur] == ' ' && line[cur - 1] != ' ') || !line[cur + 1])
			width++;
		cur++;
	}
	free(line);
	close(fd);
	return (width);
}

static void	alloc_3dmap_array(t_3Dpoint ***map, int height, int width)
{
	int	curh;
	int	curw;

	curh = 0;
	*map = (t_3Dpoint **)malloc(sizeof(t_3Dpoint *) * (height + 1));
	if (!(*map))
		exit(EXIT_FAILURE);
	(*map)[height] = 0;
	while (curh < height)
	{
		(*map)[curh] = (t_3Dpoint *)malloc(sizeof(t_3Dpoint) * (width + 1));
		if (!(*map)[curh])
			exit(EXIT_FAILURE);
		curw = 0;
		while (curw < width)
		{
			(*map)[curh][curw].x = curw;
			(*map)[curh][curw].y = curh;
			(*map)[curh][curw++].last = 0;
		}
		(*map)[curh][curw].last = 1;
		curh++;
	}
}

void	parse_map_file(char *filename, t_3Dpoint ***map)
{
	int			cur;
	int			curh;
	int			curw;
	char		*line;
	int			fd;

	alloc_3dmap_array(map, get_map_height(filename), get_map_width(filename));
	curh = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd, GNL_KEEP);
	while (line)
	{
		curw = 0;
		cur = -1;
		while (line[++cur])
			if (line[cur] >= '0' && line[cur] <= '9')
				if (cur == 0 || line[cur - 1] == ' ')
					(*map)[curh][curw++].z = ft_atoi(line + cur);
		curh++;
		free(line);
		line = get_next_line(fd, GNL_KEEP);
	}
	close(fd);
}
