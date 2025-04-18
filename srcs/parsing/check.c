/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:58:49 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/07 09:45:12 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

bool	valid_char(char c, int indic)
{
	char	*str;
	int		i;

	i = -1;
	str = "01 NSEW";
	if (indic == 1)
		str = "01NSEW";
	else
		str = "01 NSEW\n";
	while (str[++i])
		if (str[i] == c)
			return (true);
	return (false);
}

bool	validcase(char **matrix, int width, int x, int y)
{
	if (x == 0 || y == 0)
		return (false);
	if (x + 1 > tstrlen(matrix[y]))
		return (false);
	if (matrix[y][x - 1] == ' ' || matrix[y][x - 1] == '\n')
		return (false);
	if (matrix[y][x + 1] == ' ' || matrix[y][x + 1] == '\n')
		return (false);
	if (y == 0 || x == 0 || x == tstrlen(matrix[y]) - 1 || y == width)
		return (false);
	if (y - 1 >= 0)
	{
		if (x >= tstrlen(matrix[y - 1]) || matrix[y - 1][x] == ' '
			|| matrix[y - 1][x] == '\n' )
			return (false);
	}
	if (y + 1 <= width)
	{
		if (x >= tstrlen(matrix[y + 1]) || matrix[y + 1][x] == ' '
			|| matrix[y + 1][x] == '\n')
			return (false);
	}
	return (true);
}

static	bool	check(t_cub *cub, char **matrix, int x, int y)
{
	if ((!validcase(matrix, cub->map->lar, x, y))
		&& (matrix[y][x] == 'N' || matrix[y][x] == 'S'
		|| matrix[y][x] == 'E' || matrix[y][x] == 'W'))
		wgas(cub, "invalid map", NULL);
	if (matrix[y][x] == '0' && !validcase(matrix, cub->map->lar, x, y))
		return (false);
	return (true);
}

bool	validmap(t_cub *cub, char **matrix)
{
	int	stop;
	int	x;
	int	y;

	y = -1;
	stop = 0;
	while (matrix[++y])
	{
		x = -1;
		while (matrix[y][++x])
		{
			if (!valid_char(matrix[y][x], 0))
			{
				if (!stop && (matrix[y][x] == 'N' || matrix[y][x] == 'S'
						|| matrix[y][x] == 'E' || matrix[y][x] == 'W'))
					stop = 1;
				else
					wgas(cub, "invalid map", NULL);
			}
			if (!check(cub, matrix, x, y))
				return (false);
		}
	}
	return (true);
}
