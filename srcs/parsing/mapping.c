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

/// @brief checker qu'il ne soit pas sur une extremite de la map
/// checker que y - 1 ne contiennent pas d'espaces sur x
/// checker que y + 1 ne contiennent pas d'espaces sur x
/// checker que y  ne contiennent pas d'espaces sur x - 1 | x + 1
static	bool	validcase(char **matrix, int width, int x, int y)
{
	if (y == 0 || x == 0 || x == tstrlen(matrix[y]) - 1 || y == width)  // check ligne du dessus
		return (false);
	// printf("dkonqwwoidnqwodn\n");
	if (y - 1 >= 0) // check ligne du haut
		if (matrix[y - 1][x] == ' ')
			return (false);
	if (y + 1 <= width) // check ligne du bas
		if (matrix[y + 1][x] == ' ')
			return (false);
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

static void	rearrange_map(t_cub *cub, t_map *map);

void	mapping(t_cub *cub, char *save, char *line)
{
	int	width;
	int	nill;

	width = 0;
	line = gnl(cub->fd);
	while (null_line(line))
		next_line(cub, &line);
	while (line)
	{
		nill = 0;
		while (line && !tstrcmp(line, "\n"))
		{
			nill++;
			next_line(cub, &line);
			if (!null_line(line) && tstrcmp(line, "\n"))
			{
				width += nill - 10;
				break ;
			}
		}
		++width;
		if (tstrlen(line) > cub->map->l)
			cub->map->l = tstrlen(line);
		save = tjoin(save, line);
		next_line(cub, &line);
	}
	cub->map->matrix = split(save, '\n');
	cub->map->L = width - 1;
	printf("LA WIDTH EST DE %d\n", cub->map->L);
	cub->map->l -= 1; // enlever \n dans le compte
	free(save);
	if (!cub->map->matrix || !validmap(cub, cub->map->matrix))
		wgas(cub, "map invalid", NULL);
	if (cub->fd > 0)
		close(cub->fd);
	rearrange_map(cub, cub->map);
}

bool	valid_char(char c, int indic)
{
	char	*str;
	int		i;

	i = -1;
	str = "01 \tNSEW";
	if (indic)
		str = "01NSEW";
	while (str[++i])
		if (str[i] == c)
			return (true);
	return (false);
}


static	void	rearrange_map(t_cub *cub, t_map *map)
{
	char	**rearrange;
	int		i;
	int		x;

	rearrange = malloc(sizeof(char *) * (map->L + 4));
	if (!rearrange)
		wgas(cub, "rearrange map", NULL);
	rearrange[0] = malloc(sizeof(char) * (map->l + 3)); //premiere ligne
	if (!rearrange[0])
		wgas(cub, "rearrange[i] map", NULL);
	x = -1;
	while (++x < map->l + 2)
		rearrange[0][x] = '.';
	rearrange[0][x] = '\0';
	i = 0;
	while (++i < map->L + 2)
	{
		rearrange[i] = malloc(sizeof(char) * (map->l + 3));
		if (!rearrange[i])
			wgas(cub, "rearrange[i] map", NULL);
		rearrange[i][0] = '.';
		x = 0;
		while (++x < map->l + 2)
		{
			if (x > tstrlen(map->matrix[i - 1]))
			{
				while (x < map->l + 2)
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
	rearrange[i] = malloc(sizeof(char) * (map->l + 3)); //derniere
	if (!rearrange[i])
		wgas(cub, "rearrange[i] map", NULL);
	x = -1;
	while (++x < map->l + 2)
		rearrange[i][x] = '.';
	rearrange[i][x] = '\0';
	rearrange[i + 1] = NULL;
	print_map(rearrange);
	fsplit(cub->map->matrix);
	cub->map->matrix = rearrange;
}

void	print_map(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
}
