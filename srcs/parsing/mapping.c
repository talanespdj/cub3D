/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:14:13 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 15:50:35 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

static void	rearrange_map(t_cub *cub, t_map *map, char *line);
static char	**fill_matrix(t_cub *cub, t_map *map);
static void	fill_dot(t_map *map, char **line, int i);
static void	fill_last_line(t_cub *cub, t_map *map, char **rearrange, int i);

void	mapping(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	cub->map->matrix = malloc(sizeof(char *) * (cub->map->lar + 2));
	if (!cub->map->matrix)
		wgas(cub, "pblm mapping matrix", "malloc(.. (cub->map->lar + 2))");
	line = gnl(cub->fd);
	while (line && i < cub->map->lar + 1)
	{
		cub->map->matrix[i] = tdup(line);
		if (!cub->map->matrix[i])
		{
			while (line)
				next_line(cub, &line);
			wgas(cub, "monstre tdup", NULL);
		}
		next_line(cub, &line);
		i++;
	}
	cub->map->matrix[i] = NULL;
	close(cub->fd);
	if (!validmap(cub, cub->map->matrix))
		wgas(cub, "map invalid", NULL);
	rearrange_map(cub, cub->map, line);
}

static	void	rearrange_map(t_cub *cub, t_map *map, char *line)
{
	char	**rearrange;
	int		i;

	i = 0;
	while (line)
		next_line(cub, &line);
	free(line);
	rearrange = fill_matrix(cub, cub->map);
	while (++i < map->lar + 2)
	{
		rearrange[i] = NULL;
		rearrange[i] = malloc(sizeof(char) * (map->lon + 3));
		if (!rearrange[i])
		{
			fsplit(rearrange);
			wgas(cub, "rearrange[i] map", NULL);
		}
		fill_dot(cub->map, &rearrange[i], i);
	}
	fill_last_line(cub, map, rearrange, i);
}

char	**fill_matrix(t_cub *cub, t_map *map)
{
	char	**tmp;
	int		x;

	tmp = malloc(sizeof(char *) * (map->lar + 4));
	if (!tmp)
		wgas(cub, "tmp map", NULL);
	tmp[0] = malloc(sizeof(char) * (map->lon + 3));
	if (!tmp[0])
	{
		fsplit(tmp);
		wgas(cub, "tmp[i] map", NULL);
	}
	x = -1;
	while (++x < map->lon + 2)
		tmp[0][x] = '.';
	tmp[0][x] = '\0';
	return (tmp);
}

void	fill_dot(t_map *map, char **line, int i)
{
	int	x;

	x = 0;
	(*line)[x] = '.';
	while (++x < map->lon + 3)
	{
		if (x > tstrlen(map->matrix[i - 1]))
		{
			while (x < map->lon + 2)
			{
				(*line)[x] = '.';
				++x;
			}
			(*line)[x] = '\0';
			break ;
		}
		if (valid_char(map->matrix[i - 1][x - 1], 1))
			(*line)[x] = map->matrix[i - 1][x - 1];
		else
			(*line)[x] = '.';
	}
}

void	fill_last_line(t_cub *cub, t_map *map, char **rearrange, int i)
{
	int	x;

	rearrange[i] = NULL;
	rearrange[i] = malloc(sizeof(char) * (map->lon + 3));
	if (!rearrange[i])
	{
		fsplit(rearrange);
		wgas(cub, "rearrange[i] map", NULL);
	}
	x = -1;
	while (++x < map->lon + 2)
		rearrange[i][x] = '.';
	rearrange[i][x] = '\0';
	rearrange[i + 1] = NULL;
	fsplit(cub->map->matrix);
	cub->map->matrix = rearrange;
}
