/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FC_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 04:48:51 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/29 04:49:04 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/cub3d.h"

static	int	rgb_check(char *str);

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
				fill_floor(cub, line);
			else if (line[0] && line[0] == 'C')
				fill_ceiling(cub, line);
		}
		if ((cub->map->floor && cub->map->ceiling))
			break ; 
		line = cub->map->matrix[++i];
	}
	if (!cub->map->floor || !cub->map->ceiling)
		wgas(cub, "fccolors",
			"First lines should contain address Floor and ceiling value");

}

char	*rearrange_color(t_cub *cub, char *line)
{
	char	*str;
	int	i;
	int	c;

	c = 0;
	i = 1;
	if ((line[0] != 'F' && line[0] != 'C') || line[1] != ' ')
		wgas(cub, "debug", NULL);
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			c++;
	}
	str = malloc(sizeof (char) * (tstrlen(line) - c + 1));
	if (!str)
		wgas(cub, "str malloc rearrange color", NULL);
	c = 1;
	str[0] = line[0];
	str[1] = line[1];
	i = 2;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			str[++c] = line[i];
		i++;
	}
	// free(line);
	str[++c] = '\0';
	return (str);
}

void	fill_floor(t_cub *cub, char *line)
{
	char	**rgb;
	char	*floor;

	line = rearrange_color(cub, line);
	// printf("%s\n", line);
	rgb = split(line, ' ');
	free(line);
	if (!rgb)
		wgas(cub, "rgb", "split failed fill_floor");
	if (tstrcmp(rgb[0], "F") || !rgb[1])
	{
		fsplit(rgb);
		wgas(cub, "First lines should contain Floor and Ceiling RGB colors\n", NULL);
	}
	floor = erase_new_line(cub, rgb[1]);
	fsplit(rgb);
	rgb = NULL;
	rgb = split(floor, ',');
	free(floor);
	if (!rgb)
		wgas(cub, "rgb", "second split failed fill_floor");
	if (!rgb || (!(rgb[0] && rgb[1] && rgb[2]))
		|| (!rgb_check(rgb[0]) || !rgb_check(rgb[1]) || !rgb_check(rgb[2])))
	{
		fsplit(rgb);
		wgas(cub, "floor", "invalid rgb value");
	}
	cub->map->floor = (atolli(rgb[0]) << 16) | (atolli(rgb[1]) << 8) | atolli(rgb[2]);
	fsplit(rgb);
}

void	fill_ceiling(t_cub *cub, char *line)
{
	char	**rgb;
	char	*ceiling;

	line = rearrange_color(cub, line);
	rgb = split(line, ' ');
	free(line);
	if (!rgb)
		wgas(cub, "rgb", "split failed fill_ceiling");
	if (!rgb || tstrcmp(rgb[0], "C") || !rgb[1])
	{
		fsplit(rgb);
		wgas(cub, "First lines should contain floor and Ceiling RGB colors\n", NULL);
	}
	ceiling = erase_new_line(cub, rgb[1]);
	fsplit(rgb);
	rgb = NULL;
	rgb = split(ceiling, ',');
	free(ceiling);
	if (!rgb)
		wgas(cub, "rgb", "second split failed fill_ceiling");
	if (!rgb || (!(rgb[0] && rgb[1] && rgb[2]))
		|| (!rgb_check(rgb[0]) || !rgb_check(rgb[1]) || !rgb_check(rgb[2])))
	{
		fsplit(rgb);
		wgas(cub, "ceiling", "invalid rgb value");
	}
	cub->map->ceiling = (atolli(rgb[0]) << 16) | (atolli(rgb[1]) << 8) | atolli(rgb[2]);
	fsplit(rgb);
}

static	int	rgb_check(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i] && str[i + 1])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	if (!check_lli(str) || (atolli(str) < 0 || atolli(str) > 255))
		return (0);
	return (1);
}