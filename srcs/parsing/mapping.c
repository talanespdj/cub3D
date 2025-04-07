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

static void	rearrange_map(t_cub *cub, t_map *map);

void	mapping(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	cub->map->matrix = malloc(sizeof(char *) * (cub->map->lar + 2));
	if (!cub->map->matrix)
		wgas(cub, "pblm mapping matrix", "malloc(.. (cub->map->lar + 2))");
	line = gnl(cub->fd);
	while (line)
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
	free(line);
	close(cub->fd);
	if (!validmap(cub, cub->map->matrix))
		wgas(cub, "map invalid", NULL);
	rearrange_map(cub, cub->map);
}

void	length_map(t_cub *cub)
{
	char	*line;
	int		width;
	int		nill;

	width = 0;
	line = gnl(cub->fd);
	while (line)
	{
		nill = 0;
		while (line && null_linev2(line))
		{
			nill++;
			next_line(cub, &line);
			if (!null_linev2(line))
			{
				width += nill;
				break ;
			}
		}
		++width;
		if (tstrlen(line) > cub->map->lon)
			cub->map->lon = tstrlen(line) - 1;
		next_line(cub, &line);
	}
	cub->map->lon -= 1;
	cub->map->lar = width - 1;
	close(cub->fd);
	free(line);
}

static	void	rearrange_map(t_cub *cub, t_map *map)
{
	char	**rearrange;
	int		i;
	int		x;

	rearrange = malloc(sizeof(char *) * (map->lar + 4));
	if (!rearrange)
		wgas(cub, "rearrange map", NULL);
	rearrange[0] = malloc(sizeof(char) * (map->lon + 3));
	if (!rearrange[0])
	{
		fsplit(rearrange);
		wgas(cub, "rearrange[i] map", NULL);
	}
	x = -1;
	while (++x < map->lon + 2)
		rearrange[0][x] = '.';
	rearrange[0][x] = '\0';
	i = 0;
	while (++i < map->lar + 2)
	{
		rearrange[i] = NULL;
		rearrange[i] = malloc(sizeof(char) * (map->lon + 3));
		if (!rearrange[i])
		{
			fsplit(rearrange);
			wgas(cub, "rearrange[i] map", NULL);
		}
		rearrange[i][0] = '.';
		x = 0;
		while (++x < map->lon + 3)
		{
			if (x > tstrlen(map->matrix[i - 1]))
			{
				while (x < map->lon + 2)
				{
					rearrange[i][x] = '.';
					++x;
				}
				rearrange[i][x] = '\0';
				break ;
			}
			if (valid_char(map->matrix[i - 1][x - 1], 1))
				rearrange[i][x] = map->matrix[i - 1][x - 1];
			else
				rearrange[i][x] = '.';
		}
	}
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
