/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:14:13 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/30 03:14:31 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

static	void	next_line(t_cub *cub, char **line)
{
	free(*line);
	*line = gnl(cub->fd);
}

/// @brief checker qu'il ne soit pas sur une extremite de la map
/// checker que y - 1 ne contiennent pas d'espaces sur x - 1 | x | x + 1
/// checker que y + 1 ne contiennent pas d'espaces sur x - 1 | x | x + 1
/// checker que y  ne contiennent pas d'espaces sur x - 1 | x + 1
static	bool	validcase(char **matrix, int width, int x, int y)
{
	if (y == 0 || x == 0 || x == tstrlen(matrix[y]) - 1 || y == width)  // check ligne du dessus
		return (false);
	if (y - 1 >= 0) // check ligne du haut
	{
		if (tstrlen(matrix[y - 1]) <= x + 1) // ligne contienne 3 characteres au dessus de x
			return (false);
		if (x - 1 >= 0)
			if (matrix[y - 1][x - 1] == ' ')
				return (false);
		if (matrix[y - 1][x] == ' ')
			return (false);
		if (matrix[y - 1][x + 1] == ' ')
			return (false);
	}
	if (y + 1 <= width) // check ligne du bas
	{
		if (tstrlen(matrix[y + 1]) <= x + 1) // ligne contienne 3 characteres au dessus de x
			return (false);
		if (x - 1 >= 0)
			if (matrix[y + 1][x - 1] == ' ')
				return (false);
		if (matrix[y + 1][x] == ' ')
			return (false);
		if (matrix[y + 1][x + 1] == ' ')
			return (false);
	}
	if (x + 1 <= tstrlen(matrix[y])) // check ligne actuelle
	{
		if (matrix[y][x - 1] == ' ')
			return (false);
		if (matrix[y][x + 1] == ' ')
			return (false);
	}
	return (true);

}

static	bool	validmap(t_cub *cub, char **matrix)
{
	int	x;
	int	y;

	y = -1;
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
			if (matrix[y][x] == '0' && !validcase(matrix, cub->map->L, x, y))
				return (false);
	}
	return (true);
}

void	mapping(t_cub *cub, char *save, char *line)
{
	int	width = 0;

	line = gnl(cub->fd);
	while (null_line(line))
		next_line(cub, &line);
	while (!null_line(line))
	{
		++width;
		///// corriger la ligne si elle comprend des tab sinon segfault
		if (tstrlen(line) > cub->map->l)
			cub->map->l = tstrlen(line);
		while (null_line(line))
		{
			next_line(cub, &line);
			if (!null_line(line))
			{
				free(line);
				free(save);
				wgas(cub, "mapping", "Map is cut in some pieces i dont like it");
			}
		}
		save = tjoin(save, line);
		next_line(cub, &line);
	}
	cub->map->matrix = split(save, '\n');
	cub->map->L = width;
	free(save);
	if (!cub->map->matrix || !validmap(cub, cub->map->matrix))
		wgas(cub, "map invalid", NULL);
	if (cub->fd > 0)
		close(cub->fd);
}
