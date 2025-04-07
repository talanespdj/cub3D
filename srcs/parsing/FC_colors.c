/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FC_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 04:48:51 by tespandj          #+#    #+#             */
/*   Updated: 2025/04/05 15:52:31 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

void	fccolors(t_cub *cub)
{
	char	*line;
	int		i;

	i = 0;
	line = cub->map->matrix[i];
	while (line && (!cub->map->floor || !cub->map->ceiling))
	{
		if (!null_line(line))
		{
			if (line[0] && line[0] == 'F')
				fill_colors(cub, line, &cub->map->floor);
			else if (line[0] && line[0] == 'C')
				fill_colors(cub, line, &cub->map->ceiling);
		}
		if ((cub->map->floor && cub->map->ceiling))
			break ;
		line = cub->map->matrix[++i];
	}
	if (!cub->map->floor || !cub->map->ceiling)
		wgas(cub, "fccolors",
			"First lines should contain address Floor and ceiling value");
}

void	fill_colors(t_cub *cub, char *line, int *color)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (line[++i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			++i;
		if (line[i] < '0' || line[i] > '9')
			wgas(cub, "floor", "invalid rgb value");
		while (line[i] >= '0' && line[i] <= '9' && (*color & 0b11111111) < 255)
		{
			if ((int)(*((char *)color)) *10 + line[i] - '0' > 255)
				wgas(cub, "floor", "invalid rgb value");
			*((char *)color) = 10 * *((char *)color) + line[i++] - '0';
		}
		if (c < 2)
			*color <<= 8;
		while (line[i] == ' ' || line[i] == '\t')
			++i;
		if (c > 2 || ((line[i] == '\n' && c != 2) && line[i] != ','))
			wgas(cub, "floor", "invalid rgb value");
		c++;
	}
}
